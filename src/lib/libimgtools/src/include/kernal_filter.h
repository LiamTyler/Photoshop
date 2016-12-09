/*******************************************************************************
 * Name            : kernal_filter.h
 * Project         : FlashPhotoApp
 * Module          : Parent KernalFilter class
 * Description     : Header of KernalFilter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/12/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNAL_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNAL_FILTER_H_

#include <string>
#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/kernal.h"

using image_tools::PixelBuffer;

/**
 * @brief Base class for the filters that use convolution
 *
 * A Convolution Filter generates each new pixel based on the surrounding
 * pixels. It uses a Kernal object to determine which neighboring pixels to use
 * and their amounts. It describes the algorithm for applying the Kernal
 * to each of the pixels in the buffer to produce a fully filtered image.
 */

class KernalFilter : public Filter {
 public:
  explicit KernalFilter(Kernal* kernal);
  virtual ~KernalFilter();
  /**
   * @brief Generate a filtered image by convolving each pixel with its
   * neighbors
   *
   * A method that uses the Kernal* kernal_ to perform a weighted sum of
   * nearby pixels.
   *
   * @param[in] oldimage The image to apply the filter to
   * @param[out] newimage The iamge that will be produced
   *
   * @return None (newimage is where the filtered image will be)
   */
  virtual void ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage);
  virtual std::string name(void) = 0;


 private:
  /* Copy assignment/construction is disallowed */
  KernalFilter(const KernalFilter &f) = delete;
  KernalFilter& operator=(const KernalFilter &f) = delete;

  Kernal* kernal_;
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNAL_FILTER_H_
