/*******************************************************************************
 * Name            : IPNGHandler.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of IPNGHandler class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 11/13/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/
#include <png.h>
#include <cstring>
#include "lib/libimgtools/src/include/ipng_handler.h"

#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/color_data.h"

using image_tools::ColorData;
using image_tools::PixelBuffer;

// Load desired image to current buffer
PixelBuffer* IPNGHandler::LoadImage(const std::string file_name) {
    PixelBuffer* loaded_image_buffer = nullptr;
    png_image image;
    memset(&image, 0, (sizeof image));
    image.version = PNG_IMAGE_VERSION;
    // Create empty buffer with width and height of desired image
    if (png_image_begin_read_from_file(&image, file_name.c_str())) {
        loaded_image_buffer = new PixelBuffer(image.width, image.height,
                                                      ColorData(0.0, 0.0, 0.0));
        png_bytep buffer;
        image.format = PNG_FORMAT_RGBA;
        buffer = new png_byte[PNG_IMAGE_SIZE(image)];

        // Copy desired image to empty buffer created above
        if (buffer && png_image_finish_read(&image, NULL, buffer, 0, NULL)) {
            for (int y = 0; y < static_cast<int>(image.height); y++) {
                for (int x = 0; x < static_cast<int>(image.width); x++) {
                    int r, g, b, a = 0;
                    r = static_cast<int>(buffer[(y*image.width*4)+(x*4)]);
                    g = static_cast<int>(buffer[(y*image.width*4)+(x*4)+1]);
                    b = static_cast<int>(buffer[(y*image.width*4)+(x*4)+2]);
                    a = static_cast<int>(buffer[(y*image.width*4)+(x*4)+3]);
                    loaded_image_buffer->set_pixel(x, image.height-(y+1),
                            ColorData(r/255.0f, g/255.0f, b/255.0f, a/255.0f));
                }
            }
        }
        delete[] buffer;
    }
    return loaded_image_buffer;
}

// Saves desired image into a buffer
bool IPNGHandler::SaveImage(const std::string file_name,
                            const PixelBuffer* buffer_to_save) {
    bool success = false;
    png_image image;
    memset(&image, 0, (sizeof image));
    image.height = buffer_to_save->height();
    image.width = buffer_to_save->width();
    image.version = PNG_IMAGE_VERSION;
    image.opaque = NULL;
    image.format = PNG_FORMAT_RGBA;
    png_bytep buffer = new png_byte[PNG_IMAGE_SIZE(image)];

    // Pixel by pixel, saving
    for (int y = image.height-1; y >= 0; y--) {
        for (int x = 0; x < static_cast<int>(image.width); x++) {
            ColorData currentPixel = buffer_to_save->get_pixel(x, y);
            buffer[((image.height-(y+1))*image.width+x)*4] =
                          static_cast<png_byte>(currentPixel.get_red()*255.0);
            buffer[((image.height-(y+1))*image.width+x)*4+1] =
                          static_cast<png_byte>(currentPixel.get_green()*255.0);
            buffer[((image.height-(y+1))*image.width+x)*4+2] =
                          static_cast<png_byte>(currentPixel.get_blue()*255.0);
            buffer[((image.height-(y+1))*image.width+x)*4+3] =
                          static_cast<png_byte>(currentPixel.get_alpha()*255.0);
        }
    }

    if (png_image_write_to_file(&image,
                            file_name.c_str(), 0, buffer, 0, NULL) != 0) {
        success = true;
    } else {
        success = false;
    }

    delete[] buffer;
    return success;
}
