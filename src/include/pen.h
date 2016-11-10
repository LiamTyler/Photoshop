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

#ifndef SRC_INCLUDE_PEN_H_
#define SRC_INCLUDE_PEN_H_

#include "include/tool.h"

class Pen : public Tool {
 public:
  Pen(int width, int height);
  Pen();
  ~Pen();
};

#endif  // SRC_INCLUDE_PEN_H_
