/*******************************************************************************
 * Name            : eraser.cc
 * Project         : BrushWork
 * Module          : tools
 * Description     : CC file for the eraser
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
#include "include/eraser.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

Eraser::Eraser(int width, int height) : Tool(width, height) {
    tool_utilities::CreateCircle(this->get_mask(),
                                height,
                                width,
                                static_cast<double>(width) / 2);
}

Eraser::Eraser() : Eraser(21, 21) {}

Eraser::~Eraser() {}

void Eraser::ApplyTool(PixelBuffer* buff, ColorData current_color,
                        int x, int y, int last_x, int last_y) {
    std::cout << "about to apply the parent applyTool" << std::endl;
    this->Tool::ApplyTool(buff, buff->background_color(), x, y, last_x, last_y);
}
