/*******************************************************************************
 * Name            : imgtools_interface.h
 * Project         : FlashPhoto
 * Module          : imgtools_interface.h
 * Description     : Functions for things the libimgtools library
 * Copyright       : Group Bits Please 
 * Creation Date   : 12/6/16
 * Original Author : Liam Tyler
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IMGTOOLS_INTERFACE_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IMGTOOLS_INTERFACE_H_

#include <string>
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace imgtools {

void ApplyChannel(PixelBuffer* oldimage, PixelBuffer* newimage,
                  float red, float green, float blue);

void ApplySaturate(PixelBuffer* oldimage, PixelBuffer* newimage, float amt);

void ApplyBlur(PixelBuffer* oldimage, PixelBuffer* newimage, float amt);

void ApplySharpen(PixelBuffer* oldimage, PixelBuffer* newimage, float amt);

void ApplyMotionBlur(PixelBuffer* oldimage, PixelBuffer* newimage,
                     int amt, int direction);

void ApplyEdgeDetect(PixelBuffer* oldimage, PixelBuffer* newimage);

void ApplyQuantize(PixelBuffer* oldimage, PixelBuffer* newimage, int bins);

void ApplyThreshold(PixelBuffer* oldimage, PixelBuffer* newimage, float level);

void ApplySpecial(PixelBuffer* oldimage, PixelBuffer* newimage);

image_tools::PixelBuffer* LoadImage(const std::string& file_name);

bool SaveImage(const std::string& file_name,
               const image_tools::PixelBuffer* bufferToSave);

int CompareImages(const PixelBuffer* img1, const PixelBuffer* img2);

}  /* namespace imgtools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IMGTOOLS_INTERFACE_H_
