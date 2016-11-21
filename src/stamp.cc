/*******************************************************************************
 * Name            : stamp.cc
 * Project         : BrushWork
 * Module          : tools
 * Description     : CC file for the stamp
 * Copyright       : 2016 CSCI3081W Group Bits Please
 * Creation Date   : 11/20/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>
#include "include/tool.h"
#include "include/tool_utilities.h"
#include "include/stamp.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

TStamp::TStamp(int width, int height) : Tool(width, height) {
    tool_utilities::FillMask(this->get_mask(), height, width, 1.0);
}

TStamp::~TStamp() {}

void TStamp::ApplyTool(PixelBuffer* buff, ColorData current_color,
                        int x, int y, int last_x, int last_y) {
    PixelBuffer* image = image_;
    int width = this->get_width();
    int height = this->get_height();

    int mid_x = width / 2;
    int mid_y = height / 2;
    int screen_h = buff->height();
    int screen_w = buff->width();

    for (int step_y = 0; step_y < height; step_y++) {
        for (int step_x = 0; step_x < width; step_x++) {
            int cur_x = x + step_x - mid_x;
            int cur_y = screen_h - (y + step_y - mid_y);

            /* Check whether pixel will fit on the screen and
            the alpha value of the pixel of the image being stamped */
            if (cur_x >= 0 && cur_x < screen_w &&
                cur_y >= 0 && cur_y < screen_h &&
                image->get_pixel(step_x, step_y).alpha() == 1) {
                    buff->set_pixel(cur_x, cur_y,
                    image->get_pixel(step_x, step_y));
            }
        }
    }
}
