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

#ifndef SRC_INCLUDE_KERNAL_FILTER_H_
#define SRC_INCLUDE_KERNAL_FILTER_H_

#include <string>
#include "include/filter.h"
#include "include/pixel_buffer.h"
#include "include/kernal.h"

using image_tools::PixelBuffer;

class KernalFilter : public Filter {
 public:
  KernalFilter();
  explicit KernalFilter(Kernal* kernal);
  virtual ~KernalFilter();
  virtual void ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage);
  virtual std::string name(void) = 0;


 private:
  KernalFilter(const KernalFilter &f) = delete;
  KernalFilter& operator=(const KernalFilter &f) = delete;
  Kernal* kernal_;
};

#endif  // SRC_INCLUDE_KERNAL_FILTER_H_
