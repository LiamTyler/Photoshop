/*******************************************************************************
 * Name            : blur_tool.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Header of blur_tool.h
 * Copyright       : 2016 CSCI3081W Team Bits Please. All rights reserved.
 * Creation Date   : 11/13/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_BLUR_TOOL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_BLUR_TOOL_H_

#include <vector>
#include <string>
#include "lib/libimgtools/src/include/tool.h"
#include "lib/libimgtools/src/include/blur_kernal.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

class TBlur : public Tool {
 public:
  explicit TBlur(int radius);
  TBlur();
  ~TBlur();
  void ApplyTool(image_tools::PixelBuffer* buff,
                 image_tools::ColorData current_color,
                 int x, int y, int last_x, int last_y);
  std::string name(void) { return "Blur"; }

 private:
  TBlur(const TBlur& b) = delete;
  TBlur& operator=(const TBlur& b) = delete;
  void Init();
  int radius_;
  std::vector<BlurKernal> kernals_;
  image_tools::PixelBuffer *scratch_;
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_BLUR_TOOL_H_
