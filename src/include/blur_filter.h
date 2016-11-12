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
#include "include/filter.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class BlurFilter : public Filter {
 public:
  explicit BlurFilter(float amount);
  BlurFilter();
  ~BlurFilter();
  std::string name(void) { return "Blur"; }

 protected:
  void InitializeKernal();

 private:
  float amount_;
};

#endif  // SRC_INCLUDE_BLUR_FILTER_H_
