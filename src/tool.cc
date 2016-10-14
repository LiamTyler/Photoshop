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
#include "include/tool_utilities.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using image_tools::PixelBuffer;
using image_tools::ColorData;

void createCircle(double** mask, int height, int width, double radius) {
    int cent_x = width / 2;
    int cent_y = height / 2;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            if (pow(w - cent_x, 2) + pow(h - cent_y, 2) <= radius * radius) {
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

Tool::Tool(int width, int height) {
    width_ = width;
    height_ = height;
    // Allocate the memory for the 2d mask with height rows and width columns
    mask_ = new double*[height];
    for (int i = 0; i < height; i++) {
         mask_[i] = new double[width];
    }

    createSpray(mask_, height_, width_, static_cast<double>(width_) / 2);
}


Tool::Tool() : Tool(41, 41) {}

Tool::~Tool() {
    for (int i = 0; i < height_; i++) {
        delete[] mask_[i];
    }
    delete[] mask_;
}

void Tool::applyTool(PixelBuffer* buff, ColorData current_color, int x, int y) {
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

int Tool::getWidth() {
    return width_;
}

int Tool::getHeight() {
    return height_;
}
