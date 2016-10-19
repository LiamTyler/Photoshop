/*******************************************************************************
 * Name            : higlighter.cc
 * Project         : BrushWork
 * Module          : tools
 * Description     : CC file for the highlighter.cc
 * Copyright       : 2016 CSCI3081W Group Bits Please
 * Creation Date   : 10/14/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>
#include "include/tool.h"
#include "include/tool_utilities.h"
#include "include/highlighter.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

Highlighter::Highlighter(int width, int height) : Tool(width, height) {
    tool_utilities::createHighlighter(this->getMask(),
                                height,
                                width);
}

Highlighter::Highlighter() : Highlighter(5, 15) {}

Highlighter::~Highlighter() {}


void Highlighter::applyTool(PixelBuffer* buff, ColorData current_color,
                        int x, int y, int last_x, int last_y) {
    int width = this->getWidth();
    int height = this->getHeight();
    int min_width = last_x - width / 2;
    int min_height = last_y - height / 2;
    int max_width = min_width + width;
    int max_height = min_height + height;
    //std::cout << "min_width: " << min_width << ", min_height: " << min_height << std::endl;

    int mid_x = width / 2;
    int mid_y = height / 2;
    int screen_h = buff->height();
    int screen_w = buff->width();
    double** cur_mask = this->getMask();

    for (int step_y = 0; step_y < height; step_y++) {
        for (int step_x = 0; step_x < width; step_x++) {
            int cur_x = x + step_x - mid_x;
            int cur_y = screen_h - (y + step_y - mid_y);
            int ly = y + step_y - mid_y;

            if (cur_x >= 0 && cur_x < screen_w &&
                cur_y >= 0 && cur_y < screen_h &&
                !(min_width <= cur_x && cur_x < max_width && 
                 min_height <= ly && ly < max_height)) {
                    double intensity = cur_mask[step_y][step_x];
                    buff->set_pixel(cur_x, cur_y, current_color * intensity +
                            buff->get_pixel(cur_x, cur_y) * (1.0 - intensity));
            }
        }
    }
}
