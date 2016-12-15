/*******************************************************************************
 * Name            : sharpen_filter.h
 * Project         : FlashPhotoApp
 * Module          : Sharpen Filter
 * Description     : Header of Sharpen Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/12/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SHARPEN_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SHARPEN_FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/kernal_filter.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

/**
 * @brief Implements a sharpening filter using a sharpening kernal
 *
 */
class SharpenFilter : public KernalFilter {
 public:
  explicit SharpenFilter(int amount);
  std::string name(void) { return "Sharpen"; }
};

#endif  /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SHARPEN_FILTER_H_ */
