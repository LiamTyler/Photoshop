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

#ifndef SRC_INCLUDE_EDGE_DETECT_KERNAL_H_
#define SRC_INCLUDE_EDGE_DETECT_KERNAL_H_

#include <string>
#include "include/kernal.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class EdgeDetectKernal : Kernal {
 public:
  EdgeDetectKernal()

 protected:
  virtual void InitializeKernal();
};

#endif  // SRC_INCLUDE_EDGE_DETECT_KERNAL_H_
