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
    void CreateCircle(double** mask, int height, int width, double radius) {
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

    void FillMask(double** mask, int height, int width, double opacity) {
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                mask[h][w] = opacity;
            }
        }
    }

}  // namespace tool_utilities
