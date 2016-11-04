/*******************************************************************************
 * Name            : highlighter.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Header of highlighter
 * Copyright       : 2016 CSCI3081W Team Bits Please. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef INCLUDE_HIGHLIGHTER_H_
#define INCLUDE_HIGHLIGHTER_H_

#include "include/tool.h"

// Inheirit width and height from tool
class Highlighter : public Tool {
 public:
  Highlighter(int width, int height);
  Highlighter();
  ~Highlighter();
  void ApplyTool(image_tools::PixelBuffer* buff,
    image_tools::ColorData current_color, int x, int y, int last_x, int last_y);
};

#endif  // INCLUDE_HIGHLIGHTER_H_
