/*******************************************************************************
 * Name            : rainbow.cc
 * Project         : BrushWork
 * Module          : tools
 * Description     : CC file for the Rainbow class
 * Copyright       : 2016 CSCI3081W Group Bits Please
 * Creation Date   : 10/14/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "include/rainbow.h"
#include <cmath>
#include <iostream>
#include <iomanip>

using image_tools::PixelBuffer;
using image_tools::ColorData;

Rainbow::Rainbow(int width,
                int height,
                double color_offset,
                double rate_of_change) : Pen(width, height) {
    color_offset_ = color_offset;
    rate_of_change_ = rate_of_change;
}

Rainbow::Rainbow() : Pen(3, 3) {
    color_offset_ = 0;
    rate_of_change_ = .2;
}

void Rainbow::UpdateColor(double* red, double* green, double*blue) {
    color_offset_ += rate_of_change_;
    if (color_offset_ >= 360) {
        color_offset_ = 0;
    }
    double co = color_offset_;

    // Update our *red value
    if (co <= 60 || 300 <= co) {
        *red = 1.0;
    } else if (60 < co && co < 120) {
        *red = 1.0 - (co - 60.0) / 60;
    } else if (120 <= co && co <= 240) {
        *red = 0;
    } else {
        *red = (co - 240.0) / 60;
    }

    // Update our *green value
    if (0 <= co && co < 60) {
        *green = co / 60.0;
    } else if (60 <= co && co <= 180) {
        *green = 1.0;
    } else if (180 < co && co < 240) {
        *green = 1.0 - (co - 180.0) / 60;
    } else {
        *green = 0;
    }

    // Update our *blue value
    if (0 <= co && co <= 120) {
        *blue = 0.0;
    } else if (120 < co && co < 180) {
        *blue = (co - 120.0) / 60;
    } else if (180 <= co && co <= 300) {
        *blue = 1.0;
    } else {
        *blue = 1.0 - (co - 300.0) / 60;
    }
}

Rainbow::~Rainbow() {}

void Rainbow::ApplyTool(PixelBuffer* buff, ColorData current_color,
                        int x, int y, int last_x, int last_y) {
    double new_r = current_color.red();
    double new_g = current_color.green();
    double new_b = current_color.blue();
    this->UpdateColor(&new_r, &new_g, &new_b);
    ColorData new_c = ColorData(new_r, new_g, new_b);

    this->Tool::ApplyTool(buff, new_c, x, y, last_x, last_y);
}
