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
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

class ImageHandler {
 public:
  enum IMAGE_TYPE {
    PNG_IMAGE,
    JPG_IMAGE,
    UNKNOWN_IMAGE
  };

  static PixelBuffer* LoadImage(const std::string & file_name);
  static bool SaveImage(const std::string & file_name,
                        const PixelBuffer* bufferToSave);
 private:
  static IMAGE_TYPE GetImageType(const std::string & file_name);
};

#endif  // SRC_INCLUDE_IMAGE_HANDLER_H_
