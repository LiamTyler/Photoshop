/*******************************************************************************
 * Name            : sharpen_kernal.h
 * Project         : FlashPhotoApp
 * Module          : Parent SharpenKernal class
 * Description     : Header of SharpenKernal
 * Copyright       : Group Bits Please
 * Creation Date   : 11/16/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_SHARPEN_KERNAL_H_
#define SRC_INCLUDE_SHARPEN_KERNAL_H_

#include <string>
#include "include/kernal.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class SharpenKernal : public Kernal {
 public:
  explicit SharpenKernal(int amount);
  int get_amount() { return amount_; }

 protected:
  virtual void InitializeKernal();

 private:
  int amount_;
};

#endif  // SRC_INCLUDE_SHARPEN_KERNAL_H_
