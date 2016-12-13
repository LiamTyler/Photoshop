/*******************************************************************************
 * Name            : IJPGHandler.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of IJPGHandler class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 11/13/15
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "lib/libimgtools/src/include/ijpg_handler.h"
#include <iostream>
#include <cstdlib>
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/color_data.h"

using image_tools::ColorData;
using image_tools::PixelBuffer;

PixelBuffer* IJPGHandler::LoadImage(const std::string file_name) {
    PixelBuffer* loaded_image_buffer = NULL;

    // Contains parameters of JPEG decompression
    struct jpeg_decompress_struct cinfo;
    struct my_error_mgr jerr;

    FILE * infile;
    JSAMPARRAY buffer;  // output buffer
    int row_stride;  // width of buffer

    // Open the file that was inputted
    if ((infile = fopen(file_name.c_str(), "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", file_name.c_str());
        std::cout << "ERROR: CANNOT READ JPG" << std::endl;
        return nullptr;
    }

    // Now we can initialize the JPEG decompression object
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = NULL;
    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
        std::cout << "ERROR: CANNOT READ JPG" << std::endl;
        exit(1);
    }

    jpeg_create_decompress(&cinfo);

    jpeg_stdio_src(&cinfo, infile);

    (void) jpeg_read_header(&cinfo, TRUE);

    (void) jpeg_start_decompress(&cinfo);

    /*
    std::cout << "loading width: " << cinfo.output_width <<
        ", loading height: " << cinfo.output_height << std::endl;
    */

    loaded_image_buffer = new PixelBuffer(cinfo.output_width,
                                        cinfo.output_height,
                                        ColorData(0.0, 0.0, 0.0));

    // Find width of buffer
    row_stride = cinfo.output_width * cinfo.output_components;

    // Create a temporary array
    buffer = (*cinfo.mem->alloc_sarray)
             (reinterpret_cast<jpeg_common_struct*>(&cinfo),
              JPOOL_IMAGE, row_stride, 1);

    // Use the library state variable to keep track of the counter
    // Obtain colors by amount of red, green, and blue within a pixel
    int y = 0;
    while (cinfo.output_scanline < cinfo.output_height) {
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);
        for (int x = 0; x < static_cast<int>(cinfo.output_width); x++) {
            int r, g, b, a = 0;
            r = static_cast<int>(*(buffer[0]+(x*3)));
            g = static_cast<int>(*(buffer[0]+(x*3)+1));
            b = static_cast<int>(*(buffer[0]+(x*3)+2));
            a = 255;
            loaded_image_buffer->set_pixel(x, cinfo.output_height-(y+1),
                        ColorData(r/255.0f, g/255.0f, b/255.0f, a/255.0f));
        }
        y+=1;
    }

    // Finish JPEG decompression
    (void) jpeg_finish_decompress(&cinfo);

    // Free up memory
    jpeg_destroy_decompress(&cinfo);

    // close file
    fclose(infile);

    return loaded_image_buffer;
}

bool IJPGHandler::SaveImage(const std::string file_name,
                            const PixelBuffer* buffer_to_save) {
    struct jpeg_compress_struct cinfo;

    // set up error handling helper variables
    struct jpeg_error_mgr jerr;
    FILE * outfile;
    JSAMPROW row_pointer[1];
    int row_stride;

    // set up error handling
    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_compress(&cinfo);

    // Use library function to send data to stdio
    if ((outfile = fopen(file_name.c_str(), "wb")) == NULL) {
        return false;
    }
    jpeg_stdio_dest(&cinfo, outfile);

    // Set parameters from compression
    cinfo.image_width = buffer_to_save->width();
    cinfo.image_height = buffer_to_save->height();
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);

    jpeg_set_quality(&cinfo, 100, TRUE);

    // Begin compression
    jpeg_start_compress(&cinfo, TRUE);

    // Use library function for counter
    row_stride = cinfo.image_width * 3;
    const int width = buffer_to_save->width();
    const int height = buffer_to_save->height();
    JSAMPLE* image_buffer = new JSAMPLE[row_stride*cinfo.image_height];

    // Obtain colors by amount of red, green, and blue within a pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ColorData currentPixel = buffer_to_save->get_pixel(x, y);
            image_buffer[((height-(y+1))*width+x)*3] =
                             static_cast<JSAMPLE>(currentPixel.get_red()*255.0);
            image_buffer[((height-(y+1))*width+x)*3+1] =
                           static_cast<JSAMPLE>(currentPixel.get_green()*255.0);
            image_buffer[((height-(y+1))*width+x)*3+2] =
                            static_cast<JSAMPLE>(currentPixel.get_blue()*255.0);
        }
    }


    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    delete[] image_buffer;

    // End compression
    jpeg_finish_compress(&cinfo);

    // Close file
    fclose(outfile);

    // Free up memory
    jpeg_destroy_compress(&cinfo);

    return true;
}
