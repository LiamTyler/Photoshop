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
                int color_offset,
                int rate_of_change,
                int angle_offset) : Pen(width, height) {
    color_offset_ = color_offset;
    rate_of_change_ = rate_of_change;
    angle_offset_ = angle_offset;
}

Rainbow::Rainbow() : Pen(3, 3) {
    color_offset_ = 0;
    rate_of_change_ = 1;
    angle_offset_ = 0;


void Rainbow::updateAngle() {
    angle_offset_ = (angle_offset_ + 1) % 360;
}

void Rainbow::updateColor(double* red, double* green, double*blue) {
    int co = (color_offset_ + 1) % 360;

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

    /* Method with black but no purple and sharp changes
    if (0 <= co && co < 60) {
        red = co / 60.0;
    } else if (60 <= co && co <= 120) {
        red = 1.0;
    } else if (120 < co && co < 180) {
        red = 1.0 - (co - 120.0) / 60.0;
    } else {
        red = 0;
    }

    if (co <= 60 || 300 <= co) {
        green = 0;
    } else if (60 < co && co < 120) {
        green = (co - 60.0) / 60.0;
    } else if (120 <= co && co <= 240) {
        green = 1.0;
    } else {
        green = 1.0 - (co - 240.0) - 60.0;
    }

    if (0 <= co && co <= 180) {
        blue = 0;
    } else if (180 < co && co < 240) {
        blue = (co - 180.0) / 60.0;
    } else if (240 <= co && co <= 300) {
        blue = 1.0;
    } else {
        blue = 1.0 - (co - 300.0) / 60.0;
    }
    */

    color_offset_ = co;
}

Rainbow::~Rainbow() {}

void Rainbow::applyTool(PixelBuffer* buff, ColorData current_color,
                        int x, int y) {
    /* movement code
    if (last_x != -1 && last_y != -1) {
        double direction = std::atan(static_cast<double>(last_y) / last_x);
        double theta = angle_offset_ * M_PI / 180.0;
        x += this->getRadius() * 2 * std::cos(theta) *
             std::abs(std::cos(M_PI / 4 - direction));
        y += this->getRadius() * 2 * std::sin(theta) *
             std::abs(std::cos(direction));
        this->updateAngle();
    } else {
        angle_offset_ = 0;
   }
    */

    double new_r = current_color.red();
    double new_g = current_color.green();
    double new_b = current_color.blue();
    this->updateColor(&new_r, &new_g, &new_b);
    ColorData new_c = ColorData(new_r, new_g, new_b);

    this->Tool::applyTool(buff, new_c, x, y);
}
