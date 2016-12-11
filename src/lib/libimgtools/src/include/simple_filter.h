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

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SIMPLE_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SIMPLE_FILTER_H_

#include <string>
#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/color_data.h"

using image_tools::PixelBuffer;

/**
 * @brief The base class for all filters
 *
 * A Filter describes how to produce a new image based on some algorithm
 * of filtering on a current image.
 */
class SimpleFilter {
 public:
  virtual ~SimpleFilter() {}
  /**
   * @brief Apply the Simple filter to a PixelBuffer
   *
   * A method that will use ApplyToColor on each RGB in the pixel to calculate
   * what the new RGB should be for that pixel. Unaffected by neighboring
   * pixels.
   *
   * @param[in] oldimage The image to apply the filter to
   * @param[in] newimage The iamge that will be produced
   *
   * @return None (newimage is where the filtered image will be)
   */
  void ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage);
  /**
   * @brief Calculate the new value for the color that is passed in.
   *
   * @param[in] color The color to apply the algorithm to
   * @param[in] current The ColorData object of the pixel that is currently
   * being recalculated
   *
   * @return The new value of the color requested
   */
  virtual float ApplyToColor(std::string color,
                             const image_tools::ColorData& current) = 0;
  virtual std::string name(void) = 0;
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SIMPLE_FILTER_H_
