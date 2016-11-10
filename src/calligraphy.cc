/*******************************************************************************
 * Name            : calligraphy.cc
 * Project         : BrushWork
 * Module          : tools
 * Description     : CC file for the calligraphy.cc
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
#include "include/calligraphy.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;
// Call the rectangular mask from tool_utilities
TCalligraphy::TCalligraphy(int width, int height) : Tool(width, height) {
    tool_utilities::FillMask(this->get_mask(), height, width, 1.0);
}

// Set the size of the mask
TCalligraphy::TCalligraphy() : TCalligraphy(5, 15) {}

TCalligraphy::~TCalligraphy() {}
