/*******************************************************************************
 * Name            : imagehandler.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Header of ImageHandler
 * Copyright       : Group Bits Please
 * Creation Date   : 11/21/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_IMAGE_HANDLER_H_
#define SRC_INCLUDE_IMAGE_HANDLER_H_

#include <string>
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class ImageHandler {
 public:
  enum IMAGE_TYPE {
    PNG_IMAGE,
    JPG_IMAGE,
    UNKNOWN_IMAGE
  };

  static PixelBuffer* loadImage(const std::string & fileName);
  static bool saveImage(const std::string & fileName,
                        const PixelBuffer* bufferToSave);
 private:
  static IMAGE_TYPE getImageType(const std::string & fileName);
};

#endif  // SRC_INCLUDE_IMAGE_HANDLER_H_
