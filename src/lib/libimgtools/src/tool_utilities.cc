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

#include "lib/libimgtools/src/include/tool_utilities.h"
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
// also passing in the coordinates of where the "from" should be centered
// onto the "to" buffer
void CopyPixelBuffer(PixelBuffer* from, PixelBuffer* to, int x, int y) {
    int f_w = from->width();
    int f_half_w = f_w / 2;
    int f_h = from->height();
    int f_half_h = f_h / 2;
    int t_width = to->width();
    int t_height = to->height();

    // Copy the actual pixels over into the buffer, now that it has the
    // correct size and bg color
    for (int r = 0; r < f_h; r++) {
        for (int c = 0; c < f_w; c++) {
            int nx = c + x - f_half_w;
            int ny = r + y - f_half_h;
            if (0 <= nx && nx < t_width && 0 <= ny && ny < t_height)
                to->set_pixel(nx, ny, from->get_pixel(c, r));
        }
    }
}

}  // namespace tool_utilities
