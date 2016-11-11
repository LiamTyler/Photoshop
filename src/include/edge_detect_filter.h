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

#ifndef SRC_INCLUDE_EDGE_DETECT_FILTER_H_
#define SRC_INCLUDE_EDGE_DETECT_FILTER_H_

#include <string>
#include "include/filter.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class EdgeDetectFilter : public Filter {
 public:
  EdgeDetectFilter();
  ~EdgeDetectFilter();
  std::string name(void) { return "Edge Detect"; }

 protected:
  void InitializeKernal();
};

#endif  // SRC_INCLUDE_EDGE_DETECT_FILTER_H_
