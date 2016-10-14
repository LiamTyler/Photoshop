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

    void createCircle(double** mask, int height, int width, double radius) {
        int cent_x = width / 2;
        int cent_y = height / 2;
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                if (pow(w - cent_x, 2) + pow(h - cent_y, 2)
                   <= radius * radius) {
                    mask[h][w] = 1.0;
                }
            }
        }
    }


    void createSpray(double** mask, int height, int width, double radius) {
        int cent_x = width / 2;
        int cent_y = height / 2;
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                float intensity = (1.0 - (sqrt(pow(w - cent_x, 2) +
                                   pow(h - cent_y, 2)))/radius) * 0.2;

                // std::cout << "intensity = " << intensity << std::endl;
                if (intensity > 0) {
                    mask[h][w] = intensity;
                } else {
                    mask[h][w] = 0.0;
                }
            }
        }
    }

}  // namespace tool_utilities
