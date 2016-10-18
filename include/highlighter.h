/*******************************************************************************
 * Name            : highlighter.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Header of highlighter
 * Copyright       : 2016 CSCI3081W Team Bits Please. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef INCLUDE_HIGHLIGHTER_H_
#define INCLUDE_HIGHLIGHTER_H_

#include "include/tool.h"

class Highlighter : public Tool {
 public:
  Highlighter(int width, int height);
  Highlighter();
  ~Highlighter();
};

#endif  // INCLUDE_HIGHLIGHTER_H_
