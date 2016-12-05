/*******************************************************************************
 * Name            : simple_filter.h
 * Project         : FlashPhotoApp
 * Module          : Parent SimpleFilter class
 * Description     : Header of SimpleFilter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/11/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_SIMPLE_FILTER_H_
#define SRC_INCLUDE_SIMPLE_FILTER_H_

#include <string>
#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/color_data.h"

using image_tools::PixelBuffer;

class SimpleFilter {
 public:
  virtual ~SimpleFilter() {}
  void ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage);
  virtual float ApplyToColor(std::string color,
                             const image_tools::ColorData& current) = 0;
  virtual std::string name(void) = 0;
};

#endif  // SRC_INCLUDE_SIMPLE_FILTER_H_
