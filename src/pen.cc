/*******************************************************************************
 * Name            : pen.cc
 * Project         : BrushWork
 * Module          : tools
 * Description     : CC file for the Pen.cc
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

Pen::Pen(int width, int height) : Tool(width, height) {
    radius_ = static_cast<double>(width) / 2;
    tool_utilities::createCircle(this->getMask(),
                                height,
                                width,
                                radius_);
}

Pen::Pen() : Pen(3,3) {}

Pen::~Pen() {}

double Pen::getRadius() {
    return radius_;
}
