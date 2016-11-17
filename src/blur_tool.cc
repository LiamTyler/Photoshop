/*******************************************************************************
 * Name            : blur_tool.cc
 * Project         : BrushWork
 * Module          : tools
 * Description     : CC file for the blur_tool
 * Copyright       : 2016 CSCI3081W Group Bits Please
 * Creation Date   : 11/13/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "include/blur_tool.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include "include/tool_utilities.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

TBlur::TBlur(int radius) : Tool(2 * radius + 1, 2 * radius + 1),
                           radius_(radius),
                           kernals_(nullptr),
                           scratch_(nullptr) {
    float** mask = this->get_mask();

    int center = radius_;
    int diameter = 2 * radius_ + 1;
    for (int h = 0; h < diameter; h++) {
        for (int w = 0; w < diameter; w++) {
            float intensity = 1.0 - sqrt(pow(h - center, 2) +
                                   pow(w - center, 2))/radius_;

            if (intensity > 0) {
                mask[h][w] = static_cast<int>(diameter * intensity);
            } else {
                mask[h][w] = 0.0;
            }
        }
    }
    for (int h = 0; h < diameter; h++) {
        for (int w = 0; w < diameter; w++) {
            std::cout << std::setw(4) << mask[h][w];
        }
        std::cout << std::endl;
    }
}

TBlur::TBlur() : TBlur(7) {}

TBlur::~TBlur() {}
