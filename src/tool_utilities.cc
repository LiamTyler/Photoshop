/*******************************************************************************
 * Name            : tool_utilities.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of ToolUtilities class
 * Copyright       : 2016 CSCI3081W BitsPlease. All rights reserved.
 * Creation Date   : 10/14/2016
 * Original Author : BitsPlease
 *
 ******************************************************************************/

#include "include/tool_utilities.h"
#include <cmath>

namespace tool_utilities {

/* CreateCircle takes a square mask and a radius and sets all pixels
   within that radius to 1.0 */ 
void CreateCircle(float** mask, int height, int width, float radius) {
    int cent_x = width / 2;
    int cent_y = height / 2;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            /* If the distance between the pixel at (h, w) and the center of
               the mask is less than the radius, set that pixel to 1.0 */
            if (pow(w - cent_x, 2) + pow(h - cent_y, 2)
                    <= radius * radius) {
                mask[h][w] = 1.0;
            } else {
                mask[h][w] = 0.0;
            }
        }
    }
}

void FillMask(float** mask, int height, int width, float opacity) {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            mask[h][w] = opacity;
        }
    }
}

// Copy all of the pixels in the "from" buffer into the "to" buffer
// at an optional positional offset
void CopyPixelBuffer(PixelBuffer* from, PixelBuffer* to, int dx, int dy) {
    int width = from->width();
    int height = from->height();
    int t_width = to->width();
    int t_height = to->height();

    // Copy the actual pixels over into the buffer, now that it has the
    // correct size and bg color
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            if (c < t_width && r < t_height)
                to->set_pixel(c + dx, r + dy, from->get_pixel(c, r));
        }
    }
}

}  // namespace tool_utilities
