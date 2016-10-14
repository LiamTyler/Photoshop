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

#ifndef INCLUDE_PEN_H_
#define INCLUDE_PEN_H_

#include "include/tool.h"

class Pen : public Tool {
 public:
  Pen(int width, int height);
  Pen();
  ~Pen();
  double getRadius();

 private:
  double radius_;
};

#endif  // INCLUDE_PEN_H_
