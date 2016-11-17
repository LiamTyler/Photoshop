#include <stdio.h>
#include <png.h>
#include <setjmp.h>
#include <zlib.h>
#include "PixelBuffer.h"
#include "FlashPhotoApp.h"
#include "ColorData.h"
#include "BaseGfxApp.h"
#include "PngHandler.h"
#include <iostream>
#include <cstdlib>
#include "jconfig.h"
#include <cmath>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>


PixelBuffer* PngHandler::read_PNG_file (char* name, PixelBuffer* buffer)
{
     int width, height;
     png_byte color_type;
     png_byte bit_depth;
     png_bytep *row_pointers;

     FILE *infile;
     if ((infile = fopen(name, "rb")) == NULL) {
       fprintf(stderr, "can't open %s\n", name);
       exit(1);
     }

     png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
     if(!png) abort();

     png_infop info = png_create_info_struct(png);
     if(!info) abort();

     if(setjmp(png_jmpbuf(png))) abort();

     png_init_io(png, infile);

     png_read_info(png, info);

     width = png_get_image_width(png, info);
     height = png_get_image_height(png, info);
     color_type = png_get_color_type(png, info);
     bit_depth  = png_get_bit_depth(png, info);

     if(bit_depth == 16)
       png_set_strip_16(png);

     if(color_type == PNG_COLOR_TYPE_PALETTE)
       png_set_palette_to_rgb(png);

     // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
     if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
       png_set_expand_gray_1_2_4_to_8(png);

     if(png_get_valid(png, info, PNG_INFO_tRNS))
       png_set_tRNS_to_alpha(png);

     // These color_type don't have an alpha channel then fill it with 0xff.
     if(color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
       png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

     if(color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
       png_set_gray_to_rgb(png);

     png_read_update_info(png, info);

     row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
     for(int y = 0; y < height; y++) {
       row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
     }
     png_read_image(png, row_pointers);

     PixelBuffer* m_new_displayBuffer = new PixelBuffer( width, height, ColorData(1,1,0.95));
  	 for (int y=0; y < height; y++){
  	     for (int x=0; x < width; x++){ //loop through every pixel in the canvas
  	       float R =(float)row_pointers[y][(x*4)+0]/255.0;   //get red color value
  	       float G =(float)row_pointers[y][(x*4)+1]/255.0;   //get green color value
  	       float B = (float)row_pointers[y][(x*4)+2]/255.0;  //get blue color value
  	       float A = (float)row_pointers[y][(x*4)+3]/255.0;  //get alpha color value
  	       //apply the color by multiple the alpha value
  	       m_new_displayBuffer->setPixel(x, height - y -1 , buffer->getPixel(x, height - y -1)*(1-A) + ColorData(R,G,B,A)*A);
  	     }
  	 }
     delete buffer;
     buffer = m_new_displayBuffer;

     for(int y = 0; y < height; y++) {
       free(row_pointers[y]);
     }
     free(row_pointers);
     fclose(infile);
     return buffer;
}

void PngHandler::write_PNG_file (char* name, PixelBuffer* buffer)
{
    FILE *output;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    png_bytep *row_pointers;
    int m_width =  buffer->getWidth();
    int m_height = buffer->getHeight();
    output = fopen(name, "wb");
    if (output == NULL) {
      fprintf(stderr, "Could not open file for writing");
      exit(1);
    }
    // Initialize write structure
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
       fprintf(stderr, "Could not allocate write struct\n");
       exit(1);
    }

    // Initialize info structure
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
       fprintf(stderr, "Could not allocate info struct\n");
       exit(1);
    }

    // Setup Exception handling
    if (setjmp(png_jmpbuf(png_ptr))) {
       fprintf(stderr, "Error during png creation\n");
       exit(1);
    }

    png_init_io(png_ptr, output);

    // Write header (8 bit colour depth)

    png_set_IHDR(png_ptr, info_ptr,
                 m_width, m_height,
                 8, PNG_COLOR_TYPE_RGB_ALPHA,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE,
                 PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);


   row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * m_height);
   // for test only
   //  std::cout<<sizeof(png_bytep)<<std::endl;
   //  std::cout<<sizeof(png_bytep)<<std::endl;
   for(int y = 0; y < m_height; y++) {
        row_pointers[y] = (png_byte*)malloc(m_width* 4 *sizeof(png_byte));
   }
   // Write image data
   int x, y;

   for (y=0 ; y< m_height ; y++) {
      for (x=0 ; x< m_width ; x++) {
         ColorData pixelinfo = buffer->getPixel(x, m_height - y -1);
         pixelinfo = pixelinfo.clampedColor();
         row_pointers[y][(x*4)+0] = (png_byte)(pixelinfo.getRed()*255.0);
         row_pointers[y][(x*4)+1] = (png_byte)(pixelinfo.getGreen()*255.0);
         row_pointers[y][(x*4)+2] = (png_byte)(pixelinfo.getBlue()*255.0);
         row_pointers[y][(x*4)+3] = (png_byte)(pixelinfo.getAlpha()*255.0);
      }
   }

   png_write_image(png_ptr, row_pointers);
   // End write

   for(y = 0; y < m_height; y++) {
     free(row_pointers[y]);
   }
   free(row_pointers);
   fclose(output);
   //png_write_end(png_ptr, NULL);
}
