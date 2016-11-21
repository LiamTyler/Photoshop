/*******************************************************************************
 * Name            : ipnghandler.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Header of IPNGHandler
 * Copyright       : Group Bits Please
 * Creation Date   : 11/21/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_IPNG_HANDLER_H_
#define SRC_INCLUDE_IPNG_HANDLER_H_

#include <string>
#include "include/image_handler.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class IPNGHandler : public ImageHandler {
 public:
  static PixelBuffer* loadImage(const std::string fileName);
  static bool saveImage(const std::string fileName,
    const PixelBuffer* bufferToSave);
};

#endif  // SRC_INCLUDE_IPNG_HANDLER_H_
