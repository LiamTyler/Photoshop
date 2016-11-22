/*******************************************************************************
 * Name            : ipghandler.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Header of IJPGHandler
 * Copyright       : Group Bits Please
 * Creation Date   : 11/21/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/
#ifndef SRC_INCLUDE_IJPG_HANDLER_H_
#define SRC_INCLUDE_IJPG_HANDLER_H_

#include <stdio.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <string>
#include "include/image_handler.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class IJPGHandler : public ImageHandler {
 public:
  static PixelBuffer* LoadImage(const std::string file_name);
  static bool SaveImage(const std::string file_name,
                        const PixelBuffer* buffer_to_save);
 private:
  struct my_error_mgr {
    jpeg_error_mgr pub;  /* "public" fields */
    jmp_buf setjmp_buffer;  /* for return to caller */
  };
};

#endif  // SRC_INCLUDE_IJPG_HANDLER_H_
