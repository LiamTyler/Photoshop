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

#ifndef SRC_INCLUDE_EMBOSS_FILTER_H_
#define SRC_INCLUDE_EMBOSS_FILTER_H_

#include <string>
#include "include/kernal_filter.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class EmbossFilter : public KernalFilter {
 public:
  EmbossFilter();
  std::string name(void) { return "Emboss"; }
};

#endif  // SRC_INCLUDE_EMBOSS_FILTER_H_
