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

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_MOTION_BLUR_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_MOTION_BLUR_FILTER_H_

#include <string>
#include "lib/libimgtools/src/include/kernal_filter.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

class MotionBlurFilter : public KernalFilter {
 public:
  MotionBlurFilter(int amount, int direction);
  std::string name(void) { return "Motion Blur"; }
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_MOTION_BLUR_FILTER_H_
