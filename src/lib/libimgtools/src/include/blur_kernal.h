/*******************************************************************************
 * Name            : blur_kernal.h
 * Project         : FlashPhotoApp
 * Module          : Parent BlurKernal class
 * Description     : Header of BlurKernal
 * Copyright       : Group Bits Please
 * Creation Date   : 11/16/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_BLUR_KERNAL_H_
#define SRC_INCLUDE_BLUR_KERNAL_H_

#include <string>
#include "lib/libimgtools/src/include/kernal.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

class BlurKernal : public Kernal {
 public:
  explicit BlurKernal(int amount);
  BlurKernal();
  int get_amount() { return amount_; }

 protected:
  virtual void InitializeKernal();

 private:
  int amount_;
};

#endif  // SRC_INCLUDE_BLUR_KERNAL_H_
