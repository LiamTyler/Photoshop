/*******************************************************************************
 * Name            : edge_detect_filter.h
 * Project         : FlashPhotoApp
 * Module          : Edge Detect Filter
 * Description     : Header of Edge Detect Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/11/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EDGE_DETECT_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EDGE_DETECT_FILTER_H_

#include <string>
#include "lib/libimgtools/src/include/kernal_filter.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

class EdgeDetectFilter : public KernalFilter {
 public:
  EdgeDetectFilter();
  std::string name(void) { return "Edge Detect"; }
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EDGE_DETECT_FILTER_H_
