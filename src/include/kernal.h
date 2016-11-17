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

#ifndef SRC_INCLUDE_KERNAL_H_
#define SRC_INCLUDE_KERNAL_H_

#include <string>
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class Kernal {
 public:
  Kernal(int width, int height);
  virtual ~Kernal();
  void ApplyKernal(PixelBuffer* oldimage, PixelBuffer* newimage,
                           int start_x, int start_y);
  void Resize(int width, int height);
  inline int get_width() { return width_; }
  inline int get_height() { return height_; }
  inline float** get_kernal() { return kernal_; }

 protected:
  void AllocateKernal(int width, int height);
  void DeallocateKernal();
  virtual void InitializeKernal() = 0;

 private:
  Kernal(const Kernal& k) = delete;
  Kernal& operator=(const Kernal& k) = delete;
  int width_;
  int height_;
  float** kernal_;
};

#endif  // SRC_INCLUDE_KERNAL_H_
