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

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_QUANTIZE_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_QUANTIZE_FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/simple_filter.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

/**
 * @brief Implements a quantization filter
 *
 * Reduce the amount of information compromising an image by sorting each
 * pixel into one of N predefined bins that cover the full range of RGB
 * (0 - 1.0)
 */
class QuantizeFilter : public SimpleFilter {
 public:
  explicit QuantizeFilter(int bins);
  ~QuantizeFilter();
  float ApplyToColor(std::string, const ColorData& current);
  std::string name(void) { return "Quantize"; }

 private:
  int bins_;  /**< Number of bins to sort the colors into  */
};

#endif  /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_QUANTIZE_FILTER_H_ */
