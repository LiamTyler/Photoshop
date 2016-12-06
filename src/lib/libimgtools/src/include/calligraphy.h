/*******************************************************************************
 * Name            : calligraphy.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Header of calligraphy
 * Copyright       : 2016 CSCI3081W Team Bits Please. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CALLIGRAPHY_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CALLIGRAPHY_H_

#include <string>
#include "lib/libimgtools/src/include/tool.h"

// Inheirit width and height from tool
class TCalligraphy : public Tool {
 public:
  TCalligraphy(int width, int height);
  TCalligraphy();
  ~TCalligraphy();
  std::string name(void) { return "Calligraphy Pen"; }
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CALLIGRAPHY_H_
