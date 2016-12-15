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

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SATURATION_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SATURATION_FILTER_H_

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
 * @brief Implements a saturation filter
 *
 * A fitler that adjusts the colorfulness of an image. This can be used
 * to convert to grayscale, invert colors, or make things more colorful.
 */
class SaturationFilter : public SimpleFilter {
 public:
  explicit SaturationFilter(float amount);
  ~SaturationFilter();
  float ApplyToColor(std::string, const ColorData& current);
  std::string name(void) { return "Saturation"; }

 private:
  /**
   * @brief The amount to scale by. 0 = gray, -1 = invert,
   * 2 = twice the color
   */
  float amount_;
};

#endif  /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SATURATION_FILTER_H_ */
