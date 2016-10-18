/*******************************************************************************
 * Name            : spray_can.cc
 * Project         : BrushWork
 * Module          : tools
 * Description     : CC file for the spray_can
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
#include "include/spray_can.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

SprayCan::SprayCan(int width, int height) : Tool(width, height) {
    tool_utilities::createSpray(this->getMask(),
                                height,
                                width,
                                static_cast<double>(this->getWidth()) / 2);
}

SprayCan::SprayCan() : SprayCan(41, 41) {}

SprayCan::~SprayCan() {}
