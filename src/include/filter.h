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

#ifndef SRC_INCLUDE_FILTER_H_
#define SRC_INCLUDE_FILTER_H_

#include <string>
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class Filter {
 public:
  virtual ~Filter() {}
  virtual void ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage) = 0;
  virtual std::string name(void) = 0;
};

#endif  // SRC_INCLUDE_FILTER_H_
