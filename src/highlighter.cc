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

Highlighter::Highlighter() : Highlighter(15,5) {}

Highlighter::~Highlighter() {}
