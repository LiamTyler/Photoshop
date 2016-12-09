/*******************************************************************************
 * Name            : filter.h
 * Project         : FlashPhotoApp
 * Module          : Parent Filter class
 * Description     : Header of Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/10/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_H_

#include <string>
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

/**
 * @brief The base class for all filters
 *
 * A Filter describes how to produce a new image based on some algorithm
 * of filtering on a current image.
 */
class Filter {
 public:
  virtual ~Filter() {}
  /**
   * @brief Apply the filter to a PixelBuffer
   *
   * This is the method that gets called by all sublcasses of filter to apply
   * the filter on oldimage, setting the created image into newimage.
   *
   * @param[in] oldimage The image to apply the filter to
   * @param[out] newimage The iamge that will be produced
   *
   * @return None (newimage is where the filtered image will be)
   */
  virtual void ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage) = 0;
  virtual std::string name(void) = 0;
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_H_
