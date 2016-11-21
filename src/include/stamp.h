/*******************************************************************************
 * Name            : stamp.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Header of stamp
 * Copyright       : 2016 CSCI3081W Team Bits Please. All rights reserved.
 * Creation Date   : 11/20/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_STAMP_H_
#define SRC_INCLUDE_STAMP_H_

#include <string>
#include "include/tool.h"

class TStamp : public Tool {
 public:
  TStamp(int width, int height);
  virtual ~TStamp();
  void ApplyTool(image_tools::PixelBuffer* buff,
    image_tools::ColorData current_color, int x, int y, int last_x, int last_y);
  std::string name(void) { return "Stamp"; }
 private:
  image_tools::PixelBuffer* image_;
  void Init();
};

#endif  // SRC_INCLUDE_STAMP_H_
