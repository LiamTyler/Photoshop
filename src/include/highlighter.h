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

#ifndef SRC_INCLUDE_HIGHLIGHTER_H_
#define SRC_INCLUDE_HIGHLIGHTER_H_

#include <string>
#include "include/tool.h"

// Inheirit width and height from tool
class THighlighter : public Tool {
 public:
  THighlighter(int width, int height);
  THighlighter();
  ~THighlighter();
  void ApplyTool(image_tools::PixelBuffer* buff,
    image_tools::ColorData current_color, int x, int y, int last_x, int last_y);
  std::string name(void) { return "Highlighter"; }
};

#endif  // SRC_INCLUDE_HIGHLIGHTER_H_
