/*******************************************************************************
 * Name            : tool.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Header of tool
 * Copyright       : 2016 CSCI3081W Team_Bits_Please. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_TOOL_H_
#define INCLUDE_TOOL_H_

#include "include/color_data.h"
#include "include/pixel_buffer.h"

class Tool {
 public:
  Tool(int width, int height);
  Tool();
  ~Tool();
  void applyTool(image_tools::PixelBuffer* buff,
    image_tools::ColorData current_color, int x, int y);
  int getWidth();
  int getHeight();
  double** getMask();

 private:
  int width_;
  int height_;
  double** mask_;
};

#endif  // INCLUDE_TOOL_H_
