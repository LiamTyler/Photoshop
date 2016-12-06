/*******************************************************************************
 * Name            : kernal.h
 * Project         : FlashPhotoApp
 * Module          : Parent Kernal class
 * Description     : Header of Kernal
 * Copyright       : Group Bits Please
 * Creation Date   : 11/13/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNAL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNAL_H_

#include <string>
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/color_data.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

class Kernal {
 public:
  Kernal(int width, int height);
  Kernal();
  virtual ~Kernal();
  Kernal(const Kernal& k);
  Kernal& operator=(const Kernal& k);
  ColorData ApplyKernal(PixelBuffer* oldimage, int start_x, int start_y);
  void Resize(int width, int height);
  inline int get_width() { return width_; }
  inline int get_height() { return height_; }
  inline float** get_kernal() { return kernal_; }
  void print(std::ostream& out) const;

 protected:
  void AllocateKernal(int width, int height);
  void DeallocateKernal();
  virtual void InitializeKernal() = 0;

 private:
  int width_;
  int height_;
  float** kernal_;
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNAL_H_
