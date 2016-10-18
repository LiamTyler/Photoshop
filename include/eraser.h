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

#ifndef INCLUDE_ERASER_H_
#define INCLUDE_ERASER_H_

#include "include/eraser.h"

class Eraser : public Tool {
 public:
  Eraser(int width, int height);
  Eraser();
  ~Eraser();
};

#endif  // INCLUDE_ERASER_H_
