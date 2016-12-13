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

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_HIGHLIGHTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_HIGHLIGHTER_H_

#include <string>
#include "lib/libimgtools/src/include/tool.h"


/**
 * @brief Implements a highlighter tool
 *
 * Tool with a vertical rectangular mask, so that horizontal strokes are
 * fatter than vertical strokes.
 *
 */
class THighlighter : public Tool {
 public:
  THighlighter(int width, int height);
  THighlighter();
  ~THighlighter();
  void ApplyTool(image_tools::PixelBuffer* buff,
    image_tools::ColorData current_color, int x, int y, int last_x, int last_y);
  std::string name(void) { return "Highlighter"; }
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_HIGHLIGHTER_H_
