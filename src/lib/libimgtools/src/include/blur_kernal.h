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

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_BLUR_KERNAL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_BLUR_KERNAL_H_

#include <string>
#include "lib/libimgtools/src/include/kernal.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

/**
 * @brief A blur kernal
 *
 * This is used for general even blurring.
 */
class BlurKernal : public Kernal {
 public:
  explicit BlurKernal(int amount);
  BlurKernal();
  int get_amount() { return amount_; }

 protected:
  virtual void InitializeKernal();

 private:
  /**
   * @brief defines the diameter (to the nearest odd number) of the kernal
   */
  int amount_;
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_BLUR_KERNAL_H_
