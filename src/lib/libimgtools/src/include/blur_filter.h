/*******************************************************************************
 * Name            : blur_filter.h
 * Project         : FlashPhotoApp
 * Module          : Blur Filter
 * Description     : Header of Blur Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/10/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_BLUR_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_BLUR_FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/kernal_filter.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

/**
 * @brief Implements a new blur filter using a kernal that blurs equally in
 * all directions.
 */
class BlurFilter : public KernalFilter {
 public:
  explicit BlurFilter(int amount);
  std::string name(void) { return "Blur"; }
};

#endif  /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_BLUR_FILTER_H_ */
