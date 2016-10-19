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

    /* createCircle takes a square mask and a radius and sets all pixels
    within that radius to 1.0 */ 
    void createCircle(double** mask, int height, int width, double radius) {
        int cent_x = width / 2;
        int cent_y = height / 2;
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                /* If the distance between the pixel at (h, w) and the center of
                the mask is less than the radius, set that pixel to 1.0 */
                if (pow(w - cent_x, 2) + pow(h - cent_y, 2)
                   <= radius * radius) {
                    mask[h][w] = 1.0;
                }
            }
        }
    }

    /* createSpray takes a square mask and a radius and sets all pixels
    to some intensity between 0 and 0.2 depending on its distance from
    the center */
    void createSpray(double** mask, int height, int width, double radius) {
        int cent_x = width / 2;
        int cent_y = height / 2;
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                /* find the distance of the pixel at (h, w). Find the ratio
                of that distance to the radius. Subtract from 1.0, since
                intensity decreases as you get farther from the center.
                Multiply by 0.2 to get the desired intensity. */
                float intensity = (1.0 - (sqrt(pow(w - cent_x, 2) +
                                   pow(h - cent_y, 2)))/radius) * 0.2;

                if (intensity > 0) {
                    mask[h][w] = intensity;
                } else {
                    mask[h][w] = 0.0;
                }
            }
        }
    }

    void createCaligraphy(double** mask, int height, int width) {
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                mask[h][w] = 1;
            }
        }
    }

    void createHighlighter(double** mask, int height, int width) {
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                mask[h][w] = 0.4;
            }
        }
    }

}  // namespace tool_utilities
