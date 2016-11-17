/*******************************************************************************
 * Name            : motion_blur_kernal.h
 * Project         : FlashPhotoApp
 * Module          : Parent MotionBlurKernal class
 * Description     : Header of MotionBlurKernal
 * Copyright       : Group Bits Please
 * Creation Date   : 11/16/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_MOTION_BLUR_KERNAL_H_
#define SRC_INCLUDE_MOTION_BLUR_KERNAL_H_

#include <string>
#include "include/kernal.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class MotionBlurKernal : Kernal {
 public:
  MotionBlurKernal(int amount, int direction);
  inline get_amount() { return amount_; }
  inline get_direction() { return direction_; }

 protected:
  virtual void InitializeKernal();

 private:
  int amount_;
  int direction_;
};

#endif  // SRC_INCLUDE_MOTION_BLUR_KERNAL_H_
