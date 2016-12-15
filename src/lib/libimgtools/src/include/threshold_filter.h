/*******************************************************************************
 * Name            : threshold_filter.h
 * Project         : FlashPhotoApp
 * Module          : Threshold Filter
 * Description     : Header of Threshold Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/12/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_THRESHOLD_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_THRESHOLD_FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/simple_filter.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

/**
 * @brief A threshold filter
 *
 * The effect of this filter is to set the RGB components of all pixels that
 * it operates on to 1 if the RGB value is greater than the threshold, and 0
 * otherwise
 */
class ThresholdFilter : public SimpleFilter {
 public:
  explicit ThresholdFilter(float level);
  ThresholdFilter();
  ~ThresholdFilter();
  std::string name(void) { return "Threshold"; }
  float ApplyToColor(std::string color,
                     const image_tools::ColorData& current);

 private:
  float level_;
};

#endif  /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_THRESHOLD_FILTER_H_ */
