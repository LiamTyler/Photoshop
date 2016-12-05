/*******************************************************************************
 * Name            : spray_can.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Header of spray_can
 * Copyright       : 2016 CSCI3081W Team Bits Please. All rights reserved.
 * Creation Date   : 10/16/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_SPRAY_CAN_H_
#define SRC_INCLUDE_SPRAY_CAN_H_

#include <string>
#include "lib/libimgtools/src/include/tool.h"

class TSprayCan : public Tool {
 public:
  TSprayCan(int width, int height);
  TSprayCan();
  virtual ~TSprayCan();
  std::string name(void) { return "Spray Can"; }
 private:
  void Init();
};

#endif  // SRC_INCLUDE_SPRAY_CAN_H_
