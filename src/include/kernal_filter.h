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

using image_tools::PixelBuffer;

class KernalFilter : public Filter {
 public:
  KernalFilter();
  KernalFilter(int width, int height);
  virtual ~KernalFilter();
  virtual void ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage);
  virtual void CreateKernal(int width, int height);
  inline int get_width() { return width_; }
  inline int get_height() { return height_; }
  inline float** get_kernal() { return kernal_; }
  virtual std::string name(void) = 0;

 protected:
  void AllocateKernal(int width, int height);
  void DeallocateKernal();
  virtual void InitializeKernal() = 0;

 private:
  KernalFilter(const KernalFilter &f) = delete;
  KernalFilter& operator=(const KernalFilter &f) = delete;
  int width_;
  int height_;
  float** kernal_;
};

#endif  // SRC_INCLUDE_KERNAL_FILTER_H_
