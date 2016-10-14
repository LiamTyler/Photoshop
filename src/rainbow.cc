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

using image_tools::PixelBuffer;
using image_tools::ColorData;

Rainbow::Rainbow(int width,
                int height,
                double color_offset,
                int rate_of_change,
                int angle_offset) : Pen(width, height) {
    color_offset_ = color_offset;
    rate_of_change_ = rate_of_change;
    angle_offset_ = angle_offset;
}

Rainbow::Rainbow() : Pen(3,3) {
    color_offset = 0.0;
    rate_of_change = 1;
    angle_offset_ = 0.0;
}

double Rainbow::updatePosition(double angle_offset) {
    return (angle_offset + 1) % 360;
}

void Rainbow::updateColor(double& red, double& green, double& blue) {
    co = (color_offset_ + 1) % 360;
    
    // Update our red value
    if (0 <= co && co <= 60 || co <= 300 && co <= 360) {
        red = 1.0;
    } else if (60 < co && co < 120) {
        red = 1.0 - (co - 60.0) / 60;
    } else if (120 <= co && co <= 240) {
        red = 0;
    } else {
        red = (co - 300.0) / 60;
    }

    // Update our green value
    if (0 <= co && co < 60) {
        green = co / 60.0;
    } else if (60 <= co && co <= 180) {
        green = 1.0;
    } else if (180 < co && co < 240) {
        green = 1.0 - (co - 240.0) / 60;
    } else {
        green = 0;
    }

    // Update our blue value
    if (0 <= co && co <= 120) {
        blue = 0.0;
    } else if (120 < co && co < 180) {
        blue = (co - 180.0) / 60;
    } else if (180 <= co && co <= 300) {
        blue = 1.0;
    } else {
        blue = 1.0 - (co - 360.0) / 60;
    }

    color_offset_ = co;
}

Rainbow::~Rainbow() {}

void Rainbow::applyTool(PixelBuffer* buff, ColorData current_color, int x, int y) {
    x += this->getRadius() * cos(angle_offset);
    y += this->getRadius() * sin(angle_offset);
    int mid_x = width_ / 2;
    int mid_y = height_ / 2;
    int screen_h = buff->height();
    int screen_w = buff->width();

    for (int step_x = 0; step_x < width_; step_x++) {
        for (int step_y = 0; step_y < height_; step_y++) {
            int cur_x = x + step_x - mid_x;
            // Needs to be buff->height() - y because pixels buffer's
            // 0,0 is the lower left
            // corner, while in brushwork, 0,0 is the upper left
            int cur_y = screen_h - (y + step_y - mid_y);
            if (cur_x >= 0 && cur_x < screen_w &&
                cur_y >= 0 && cur_y < screen_h) {
                    double intensity = mask_[step_x][step_y];
                    // copy constructor
                    buff->set_pixel(cur_x, cur_y, current_color * intensity +
                            buff->get_pixel(cur_x, cur_y) * (1.0 - intensity));
            }
        }
    }
}
