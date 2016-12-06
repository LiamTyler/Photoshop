/*******************************************************************************
 * Name            : rainbow.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Header of rainbow
 * Copyright       : 2016 CSCI3081W Team Bits Please. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_RAINBOW_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_RAINBOW_H_

#include <string>
#include "lib/libimgtools/src/include/pen.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/color_data.h"

class TRainbow : public Tool {
 public:
  TRainbow(int width, int height, double color_offset, double rate_of_change);
  TRainbow();
  ~TRainbow();
  // Override the applyTool so we can update the color before we apply the mask
  void ApplyTool(image_tools::PixelBuffer* buff,
                image_tools::ColorData current_color,
                int x, int y, int last_x, int last_y);
  // Cycle the color through the color wheel acording to this algorithm:
  // http://academe.co.uk/wp-content/uploads/2012/04/
  // 451px-HSV-RGB-comparison.svg_.png
  void UpdateColor(double* red, double* green, double* blue);
  std::string name(void) { return "Rainbow Pen"; }

 private:
  double color_offset_;  // Angle through the color wheel
  double rate_of_change_;  // How quickly the color will change
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_RAINBOW_H_
