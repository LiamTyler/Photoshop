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

#ifndef INCLUDE_RAINBOW_H_
#define INCLUDE_RAINBOW_H_

#include "include/pen.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"

class Rainbow : public Pen {
 public:
  Rainbow(int width, int height, int color_offset, int rate_of_change,
          int angle_offset);
  Rainbow();
  ~Rainbow();
  void applyTool(image_tools::PixelBuffer* buff,
                image_tools::ColorData current_color,
                int x, int y);
  void updateAngle();
  void updateColor(double* red, double* green, double* blue);

 private:
  int color_offset_;  // Angle through the color wheel
  int rate_of_change_;  // How quickly the color will change
  int angle_offset_;  // Theta in the equation y = r*sin(theta)
};

#endif  // INCLUDE_RAINBOW_H_
