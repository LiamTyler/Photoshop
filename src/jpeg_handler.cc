#include <stdio.h>
#include "jpeglib.h"
#include <setjmp.h>
#include "PixelBuffer.h"
#include "FlashPhotoApp.h"
#include "ColorData.h"
#include "BaseGfxApp.h"
#include "JpegHandler.h"
#include <iostream>
#include <cstdlib>
#include "jconfig.h"
#include <cmath>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

PixelBuffer* JpegHandler::read_JPEG_file (char* name, PixelBuffer* buffer)
{
    unsigned char *raw_image = NULL;
    /* From example.c in JPEG library
    *This struct contains the JPEG compression parameters and pointers to
    * working space (which is allocated as needed by the JPEG library).
    */
    struct jpeg_decompress_struct cinfo;
    /* From example.c in JPEG library
    * This struct represents a JPEG error handler.  It is declared separately
    * because applications often want to supply a specialized error handler
    * (see the second half of this file for an example).
    */
    struct jpeg_error_mgr jerr;
     /* libjpeg data structure for storing one row, that is, scanline of an image */
    JSAMPROW row_pointer[1];		/* pointer to JSAMPLE row[s] */
    int row_stride;		/* physical row width in output buffer */

    FILE *infile;
    if ((infile = fopen(name, "rb")) == NULL) {
      fprintf(stderr, "can't open %s\n", name);
      exit(1);
    }

    unsigned long location = 0;

     /* here we set up the standard libjpeg error handler */
    cinfo.err = jpeg_std_error( &jerr);

     /* setup decompression process and source, then read JPEG header */
    jpeg_create_decompress( &cinfo );
     /* this makes the library read from infile */
    jpeg_stdio_src( &cinfo, infile );
     /* reading the image header which contains image information */
    (void) jpeg_read_header( &cinfo, TRUE );

    /* Start decompression jpeg here */
    (void) jpeg_start_decompress(&cinfo);

    /* allocate memory to hold the uncompressed image */

    raw_image = (unsigned char*)malloc( cinfo.output_width*cinfo.output_height*cinfo.num_components );

    /* now actually read the jpeg into the raw buffer */
    row_pointer[0] = (unsigned char *)malloc( cinfo.output_width*cinfo.num_components );

    /* read one scan line at a time */
    while( cinfo.output_scanline < cinfo.output_height)
    {
        (void) jpeg_read_scanlines( &cinfo, row_pointer, 1 );
        for( int i=0; i<cinfo.image_width*cinfo.num_components;i++)
            raw_image[location++] = row_pointer[0][i];
    }

    /*initialize a new displayBuffer using image size (cinfo.image_width, cinfo.image_height, ColorData(1,1,0.95));
     * red the information of each pixel of the image and convert it to ColorData type we have
     * get red, green and blue color and divide by 255
    */

    (void) jpeg_finish_decompress( &cinfo );
    PixelBuffer *m_new_displayBuffer =new PixelBuffer(cinfo.image_width, cinfo.image_height, ColorData(1,1,0.95));
    for (int i=0; i < cinfo.image_height; i++){
        for (int j=0; j < cinfo.image_width; j++){
            float R =(float)raw_image[(i*cinfo.image_width*3)+(j*3)+0]/255.0; // Red Pixel
            float G =(float)raw_image[(i*cinfo.image_width*3)+(j*3)+1]/255.0; // Green Pixel
            float B = (float)raw_image[(i*cinfo.image_width*3)+(j*3)+2]/255.0; // Blue Pixel
            int row_offset = 0;
            //apply the each pixel to the new buffer
            m_new_displayBuffer->setPixel(j,cinfo.image_height - i -1 , ColorData(R,G,B));
        }
    }

    /*change the size of current canvas
     *delete old displayBuffer
     *replace with the new displayBuffer we create
     *using the function setWindowDimensions to set the canvas size same as the image size
    */
    delete buffer;
    buffer = m_new_displayBuffer;

    //destroy objects, free pointers and close open files
    jpeg_destroy_decompress( &cinfo );
    free( row_pointer[0] );
    fclose( infile );
    return buffer;
}


void JpegHandler::write_JPEG_file (char* name, PixelBuffer* buffer)
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    unsigned char *raw_image = NULL;
    JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    FILE * outfile;		/* target file */
    if ((outfile = fopen(name, "wb")) == NULL) {
        fprintf(stderr, "can't open %s\n", name);
        exit(1);
    }
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = buffer->getWidth(); 	/* image width and height, in pixels */
    cinfo.image_height = buffer->getHeight();
    cinfo.input_components = 3;		/* # of color components per pixel */
    cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */

    jpeg_set_defaults(&cinfo);
    //jpeg_set_quality(&cinfo, 100, TRUE);
    //cinfo.dct_method = JDCT_FLOAT;
    jpeg_start_compress(&cinfo, TRUE);

    raw_image = (unsigned char *)malloc(cinfo.image_width*cinfo.image_height*3);
    ColorData pixelinfo;
    int offset;
    for (int y=0; y < cinfo.image_height; y++){
        for (int x=0; x < cinfo.image_width; x++){
            offset = (y * cinfo.image_width * 3) + (x * 3);
            pixelinfo = buffer->getPixel(x, cinfo.image_height - y -1);
            pixelinfo = pixelinfo.clampedColor();
            raw_image[offset+0] = (pixelinfo.getRed()*255.0);
            raw_image[offset+1] = (pixelinfo.getGreen()*255.0);
            raw_image[offset+2] = (pixelinfo.getBlue()*255.0);
        }
    }
    while( cinfo.next_scanline < cinfo.image_height )
    {
        row_pointer[0] = &raw_image[cinfo.next_scanline * cinfo.image_width * 3];
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);
    free(raw_image);

}

