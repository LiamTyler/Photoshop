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
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

class Tool {
 public:
  Tool(int width, int height);
  Tool();
  virtual ~Tool();
  virtual void ApplyTool(image_tools::PixelBuffer* buff,
    image_tools::ColorData current_color, int x, int y, int last_x, int last_y);
  virtual void UpdateTool(int width, int height) {}
  inline int get_width() { return width_; }
  inline int get_height() { return height_; }
  inline void set_width(int w) { width_ = w; }
  inline void set_height(int h) { height_ = h; }
  inline float** get_mask() { return mask_; }
  virtual std::string name(void) = 0;

 private:
  Tool(const Tool &t) = delete;
  Tool& operator=(const Tool &t) = delete;
  void AllocateMask();
  int width_;
  int height_;
  float** mask_;
};

#endif  // SRC_INCLUDE_TOOL_H_
