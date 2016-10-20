/*******************************************************************************
 * Name            : tool.cc
 * Project         : BrushWork
 * Module          : tools
 * Description     : CC file for the Tool class
 * Copyright       : 2016 CSCI3081W Group Bits Please
 * Creation Date   : 10/14/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "include/tool.h"
#include <cmath>
#include <iomanip>
#include <iostream>

using image_tools::PixelBuffer;
using image_tools::ColorData;

Tool::Tool(int width, int height) {
    width_ = width;
    height_ = height;
    // Allocate the memory for the 2d mask with height rows and width columns
    mask_ = new double*[height];
    for (int i = 0; i < height; i++) {
         mask_[i] = new double[width];
    }
}

Tool::Tool() : Tool(41, 41) {}

Tool::~Tool() {
    for (int i = 0; i < height_; i++) {
        delete[] mask_[i];
    }
    delete[] mask_;
}

void Tool::ApplyTool(PixelBuffer* buff, ColorData current_color,
                    int x, int y, int last_x, int last_y) {
    int mid_x = width_ / 2;
    int mid_y = height_ / 2;
    int screen_h = buff->height();
    int screen_w = buff->width();

    for (int step_y = 0; step_y < height_; step_y++) {
        for (int step_x = 0; step_x < width_; step_x++) {
            int cur_x = x + step_x - mid_x;
            // Needs to be buff->height() - y because pixels buffer's
            // 0,0 is the lower left
            // corner, while in brushwork, 0,0 is the upper left
            int cur_y = screen_h - (y + step_y - mid_y);
            if (cur_x >= 0 && cur_x < screen_w &&
                cur_y >= 0 && cur_y < screen_h) {
                    double intensity = mask_[step_y][step_x];
                    // copy constructor
                    buff->set_pixel(cur_x, cur_y, current_color * intensity +
                            buff->get_pixel(cur_x, cur_y) * (1.0 - intensity));
            }
        }
    }
}

int Tool::get_width() {
    return width_;
}

int Tool::get_height() {
    return height_;
}

double** Tool::get_mask() {
    return mask_;
}
