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

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SHARPEN_KERNAL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SHARPEN_KERNAL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/kernal.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;


/**
 * @brief A sharpening kernel
 *
 * Defines a kernel that filters the colors of surrounding pixels out of each
 * pixel, resulting in a sharper image when convolved with an image.
 * Can be thought of as a high-pass filter.
 */
class SharpenKernal : public Kernal {
 public:
  explicit SharpenKernal(int amount);
  SharpenKernal();
  int get_amount() { return amount_; }

 protected:
  virtual void InitializeKernal();

 private:
  int amount_;  /// Amount to sharpen by. The higher the sharper.
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SHARPEN_KERNAL_H_
