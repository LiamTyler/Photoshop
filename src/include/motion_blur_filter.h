/*******************************************************************************
 * Name            : motion_blur_filter.h
 * Project         : FlashPhotoApp
 * Module          : MotionBlur Filter
 * Description     : Header of MotionBlur Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/13/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_MOTION_BLUR_FILTER_H_
#define SRC_INCLUDE_MOTION_BLUR_FILTER_H_

#include <string>
#include "include/kernal_filter.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class MotionBlurFilter : public KernalFilter {
 public:
  MotionBlurFilter(float amount, int direction);
  ~MotionBlurFilter() {}
  std::string name(void) { return "Motion Blur"; }

 protected:
  void InitializeKernal();

 private:
  float amount_;
  int direction_;
};

#endif  // SRC_INCLUDE_MOTION_BLUR_FILTER_H_
