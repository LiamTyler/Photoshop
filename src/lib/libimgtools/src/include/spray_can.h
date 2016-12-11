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

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SPRAY_CAN_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SPRAY_CAN_H_

#include <string>
#include "lib/libimgtools/src/include/tool.h"

/**
 * @brief Implements a spray can tool
 *
 * The spray can is a circular tool that has a linear falloff, so that there
 * is more paint sprayed near the middle than the edges.
 *
 */
class TSprayCan : public Tool {
 public:
  TSprayCan(int width, int height);
  TSprayCan();
  virtual ~TSprayCan();
  std::string name(void) { return "Spray Can"; }
 private:
  void Init();
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SPRAY_CAN_H_
