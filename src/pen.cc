/*******************************************************************************
 * Name            : pen.cc
 * Project         : BrushWork
 * Module          : tools
 * Description     : CC file for the TPen.cc
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
#include "include/pen.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

TPen::TPen(int width, int height) : Tool(width, height) {
    tool_utilities::CreateCircle(this->get_mask(),
                                height,
                                width,
                                static_cast<float>(width) / 2);
}

TPen::TPen() : TPen(3, 3) {}

TPen::~TPen() {}

