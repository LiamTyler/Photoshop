/*******************************************************************************
 * Name            : caligraphy.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Header of caligraphy
 * Copyright       : 2016 CSCI3081W Team Bits Please. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef INCLUDE_CALIGRAPHY_H_
#define INCLUDE_CALIGRAPHY_H_

#include "include/tool.h"

//Inheirit width and height from tool
class Caligraphy : public Tool {
 public:
  Caligraphy(int width, int height);
  Caligraphy();
  ~Caligraphy();
};

#endif  // INCLUDE_CALIGRAPHY_H_
