/*******************************************************************************
 * Name            : simple_filter.cc
 * Project         : FlashPhotoApp
 * Module          : Parent SimpleFilter class
 * Description     : CC of SimpleFilter class
 * Copyright       : Group Bits Please
 * Creation Date   : 11/10/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include <string>
#include <iostream>
#include <iomanip>
#include "lib/libimgtools/src/include/simple_filter.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/color_data.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

void SimpleFilter::ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage) {
    int buff_height = oldimage->height();
    int buff_width = oldimage->width();
    ColorData current;
    ColorData newColor;

    for (int r = 0; r < buff_height; r++) {
        for (int c = 0; c < buff_width; c++) {
            current = oldimage->get_pixel(c, r);
            newColor.red(ApplyToColor("red", current));
            newColor.green(ApplyToColor("green", current));
            newColor.blue(ApplyToColor("blue", current));
            newColor.alpha(current.get_alpha());
            newimage->set_pixel(c, r, newColor.clamped_color());
        }
    }
}
