/*******************************************************************************
 * Name            : saturation_filter.h
 * Project         : FlashPhotoApp
 * Module          : Saturation Filter
 * Description     : Header of Saturation Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/17/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_SATURATION_FILTER_H_
#define SRC_INCLUDE_SATURATION_FILTER_H_

#include <string>
#include "lib/libimgtools/src/include/simple_filter.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

class SaturationFilter : public SimpleFilter {
 public:
  explicit SaturationFilter(float amount);
  ~SaturationFilter();
  float ApplyToColor(std::string, const ColorData& current);
  std::string name(void) { return "Saturation"; }

 private:
  float amount_;
};

#endif  // SRC_INCLUDE_SATURATION_FILTER_H_
