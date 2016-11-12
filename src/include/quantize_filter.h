/*******************************************************************************
 * Name            : quantize_filter.h
 * Project         : FlashPhotoApp
 * Module          : Quantize Filter
 * Description     : Header of Quantize Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/11/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_QUANTIZE_FILTER_H_
#define SRC_INCLUDE_QUANTIZE_FILTER_H_

#include <string>
#include "include/simple_filter.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

class QuantizeFilter : public SimpleFilter {
 public:
  explicit QuantizeFilter(int bins);
  ~QuantizeFilter();
  float ApplyToColor(std::string, const ColorData& current);
  std::string name(void) { return "Quantize"; }

 private:
  int bins_;
};

#endif  // SRC_INCLUDE_QUANTIZE_FILTER_H_
