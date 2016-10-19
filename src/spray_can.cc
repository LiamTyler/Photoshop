/*******************************************************************************
 * Name            : spray_can.cc
 * Project         : BrushWork
 * Module          : tools
 * Description     : CC file for the spray_can
 * Copyright       : 2016 CSCI3081W Group Bits Please
 * Creation Date   : 10/16/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>
#include "include/tool.h"
#include "include/tool_utilities.h"
#include "include/spray_can.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

SprayCan::SprayCan(int width, int height) : Tool(width, height) {
    double radius = static_cast<double>(width) / 2;
    double** mask = this->getMask();
    
    /* Sets all pixels to some intensity between 0 and 0.2
       depending on its distance from the center */
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

// Default SprayCan size is 41 x 41
SprayCan::SprayCan() : SprayCan(41, 41) {}

SprayCan::~SprayCan() {}
