/*******************************************************************************
 * Name            : pen.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Header of pen
 * Copyright       : 2016 CSCI3081W Team Bits Please. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_PEN_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_PEN_H_

#include <string>
#include "lib/libimgtools/src/include/tool.h"

/**
 * @brief This tool simulates the usage of a Pen
 * It has a constant mask of a circle (diameter of 3) and an
 * opacity of 1.0
 */
class TPen : public Tool {
 public:
  TPen(int width, int height);
  TPen();
  ~TPen();
  std::string name(void) { return "Pen"; }
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_PEN_H_
