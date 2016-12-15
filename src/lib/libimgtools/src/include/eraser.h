/*******************************************************************************
 * Name            : eraser.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Header of eraser
 * Copyright       : 2016 CSCI3081W Team Bits Please. All rights reserved.
 * Creation Date   : 10/16/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_ERASER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_ERASER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/eraser.h"

/**
* @brief Implements an eraser tool
*
* Tool with a vertical circular mask that restore the pixels to the background color
*/
class TEraser : public Tool {
 public:
  TEraser(int width, int height);
  TEraser();
  ~TEraser();
  void ApplyTool(image_tools::PixelBuffer* buff,
                image_tools::ColorData current_color,
                int x, int y, int last_x, int last_y);
  std::string name(void) { return "Eraser"; }
};
#endif  /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_ERASER_H_ */
