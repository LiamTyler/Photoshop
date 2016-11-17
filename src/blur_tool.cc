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
#include <algorithm>
#include "include/blur_kernal.h"
#include "include/tool_utilities.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

TBlur::TBlur(int radius) : Tool(2 * radius + 1, 2 * radius + 1),
                           radius_(radius),
                           kernals_(std::vector<BlurKernal>()),
                           scratch_(nullptr) {
    float** mask = this->get_mask();
    // TODO(tyler147): move all of this out of the constructor
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

    // Allocate and Create the kernal map. Essentially, the mask created
    // above is a circle where the highest number is in the middle, and
    // it has a linear falloff. The number at each element is the radius
    // of the BlurKernal that is going to be applied to that pixel.
    // The linear falloff makes it so that the middle pixel will be very
    // blurred, while the ones on the edges aren't so much
    int filled[diameter + 1] = {0};

    for (int h = 0; h < diameter; h++)
        for (int w = 0; w < diameter; w++)
            filled[static_cast<int>(mask[h][w])] = 1;

    for (int i = 0; i < diameter + 1; i++) {
        if (!filled[i])
            kernals_.push_back(BlurKernal());
        else
            kernals_.push_back(BlurKernal(i));
    }

    // Allocate the scratch buffer to place our partially blurred
    // work onto
    scratch_ = new ColorData*[diameter];
    for (int i = 0; i < diameter; i++)
        scratch_[i] = new ColorData[diameter];

    for (int h = 0; h < diameter; h++) {
        for (int w = 0; w < diameter; w++) {
            std::cout << std::setw(4) << mask[h][w];
        }
        std::cout << std::endl;
    }
}

TBlur::TBlur() : TBlur(7) {}

TBlur::~TBlur() {
    // Free the scratch buffer
    int diameter = 2 * radius_ + 1;
    for (int h = 0; h < diameter; h++)
        delete scratch_[h];
    delete[] scratch_;
}

/*
void TBlur::ApplyTool(PixelBuffer* buff, ColorData current_color,
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
                    float intensity = mask_[step_y][step_x];
                    // copy constructor
                    buff->set_pixel(cur_x, cur_y, current_color * intensity +
                            buff->get_pixel(cur_x, cur_y) * (1.0 - intensity));
            }
        }
    }
}
*/
