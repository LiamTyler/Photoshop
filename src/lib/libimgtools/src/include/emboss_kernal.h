/*******************************************************************************
 * Name            : emboss_kernal.h
 * Project         : FlashPhotoApp
 * Module          : Parent EmbossKernal class
 * Description     : Header of EmbossKernal
 * Copyright       : Group Bits Please
 * Creation Date   : 11/17/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EMBOSS_KERNAL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EMBOSS_KERNAL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/kernal.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

/**
 * @brief an embossing kernal that finds surrounding pixels and embosses them
 */
class EmbossKernal : public Kernal {
 public:
  EmbossKernal();

 protected:
  virtual void InitializeKernal();
};

#endif  /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EMBOSS_KERNAL_H_ */
