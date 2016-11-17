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

#ifndef SRC_INCLUDE_BLUR_TOOL_H_
#define SRC_INCLUDE_BLUR_TOOL_H_

#include <string>
#include "include/tool.h"
#include "include/kernal.h"
#include "include/color_data.h"

class TBlur : public Tool {
 public:
  explicit TBlur(int radius);
  TBlur();
  ~TBlur();
  std::string name(void) { return "Blur"; }

 private:
  TBlur(const TBlur& b) = delete;
  TBlur& operator=(const TBlur& b) = delete;
  int radius_;
  Kernal** kernals_;
  image_tools::ColorData** scratch_;
};

#endif  // SRC_INCLUDE_BLUR_TOOL_H_
