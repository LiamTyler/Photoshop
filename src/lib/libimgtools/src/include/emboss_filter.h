/*******************************************************************************
 * Name            : emboss_filter.h
 * Project         : FlashPhotoApp
 * Module          : Emboss Filter
 * Description     : Header of Emboss Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/17/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EMBOSS_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EMBOSS_FILTER_H_

#include <string>
#include "lib/libimgtools/src/include/kernal_filter.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

class EmbossFilter : public KernalFilter {
 public:
  EmbossFilter();
  std::string name(void) { return "Emboss"; }
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EMBOSS_FILTER_H_
