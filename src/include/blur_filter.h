/*******************************************************************************
 * Name            : blur_filter.h
 * Project         : FlashPhotoApp
 * Module          : Blur Filter
 * Description     : Header of Blur Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/10/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_BLUR_FILTER_H_
#define SRC_INCLUDE_BLUR_FILTER_H_

#include <string>
#include "include/kernal_filter.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class BlurFilter : public KernalFilter {
 public:
  explicit BlurFilter(int amount);
  std::string name(void) { return "Blur"; }
};

#endif  // SRC_INCLUDE_BLUR_FILTER_H_
