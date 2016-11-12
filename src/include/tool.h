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

#ifndef SRC_INCLUDE_TOOL_H_
#define SRC_INCLUDE_TOOL_H_

#include <string>
#include "include/color_data.h"
#include "include/pixel_buffer.h"

class Tool {
 public:
  Tool(int width, int height);
  Tool();
  virtual ~Tool();
  virtual void ApplyTool(image_tools::PixelBuffer* buff,
    image_tools::ColorData current_color, int x, int y, int last_x, int last_y);
  int get_width();
  int get_height();
  float** get_mask();
  virtual std::string name(void) = 0;

 private:
  Tool(const Tool &t) = delete;
  Tool& operator=(const Tool &t) = delete;
  int width_;
  int height_;
  float** mask_;
};

#endif  // SRC_INCLUDE_TOOL_H_
