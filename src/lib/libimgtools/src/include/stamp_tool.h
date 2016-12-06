/*******************************************************************************
 * Name            : stamp_tool.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Header of TStamp
 * Copyright       : Group Bits Please
 * Creation Date   : 11/20/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_STAMP_TOOL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_STAMP_TOOL_H_

#include <string>
#include "lib/libimgtools/src/include/tool.h"

using image_tools::PixelBuffer;

class TStamp : public Tool {
 public:
  TStamp();
  virtual ~TStamp();
  void LoadImage(PixelBuffer* l_img);
  void ApplyTool(PixelBuffer* buff,
    image_tools::ColorData current_color, int x, int y, int last_x, int last_y);
  std::string name(void) { return "Stamp"; }
 private:
  TStamp(const TStamp& t) = delete;
  TStamp& operator=(const TStamp& t) = delete;
  PixelBuffer* image_;
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_STAMP_TOOL_H_
