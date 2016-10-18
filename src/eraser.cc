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
    tool_utilities::createCircle(this->getMask(),
                                height,
                                width,
                                static_cast<double>(this->getWidth()) / 2);
}

Eraser::Eraser() : Eraser(21, 21) {}

Eraser::~Eraser() {}
