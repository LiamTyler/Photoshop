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
  Filter();
  Filter(int width, int height);
  virtual ~Filter();
  virtual void ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage);
  virtual void CreateKernal(int width, int height);
  inline int get_width() { return width_; }
  inline int get_height() { return height_; }
  inline double** get_kernal() { return kernal_; }
  virtual std::string name(void) = 0;

 protected:
  void AllocateKernal(int width, int height);
  void DeallocateKernal();
  virtual void InitializeKernal() = 0;

 private:
  Filter(const Filter &f) = delete;
  Filter& operator=(const Filter &f) = delete;
  int width_;
  int height_;
  double** kernal_;
};

#endif  // SRC_INCLUDE_FILTER_H_
