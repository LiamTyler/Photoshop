/*******************************************************************************
 * Name            : sharpen_filter.h
 * Project         : FlashPhotoApp
 * Module          : Sharpen Filter
 * Description     : Header of Sharpen Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/12/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_SHARPEN_FILTER_H_
#define SRC_INCLUDE_SHARPEN_FILTER_H_

#include <string>
#include "include/kernal_filter.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class SharpenFilter : public KernalFilter {
 public:
  explicit SharpenFilter(int amount);
  std::string name(void) { return "Sharpen"; }
};

#endif  // SRC_INCLUDE_SHARPEN_FILTER_H_
