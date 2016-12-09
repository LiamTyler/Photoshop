/*******************************************************************************
 * Name            : edge_detect_kernal.h
 * Project         : FlashPhotoApp
 * Module          : Parent EdgeDetectKernal class
 * Description     : Header of EdgeDetectKernal
 * Copyright       : Group Bits Please
 * Creation Date   : 11/16/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EDGE_DETECT_KERNAL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EDGE_DETECT_KERNAL_H_

#include <string>
#include "lib/libimgtools/src/include/kernal.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

/**
 * @brief An edge detection kernal
 *
 * Defines a kernal that highlights edges between colors, and turns everything
 * else to black.
 */
class EdgeDetectKernal : public Kernal {
 public:
  EdgeDetectKernal();

 protected:
  virtual void InitializeKernal();
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EDGE_DETECT_KERNAL_H_
