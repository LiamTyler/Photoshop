#ifndef INCLUDE_TOOL_UTILITIES_H_
#define INCLUDE_TOOL_UTILITIES_H_

/*******************************************************************************
 * Name            : tool_utilities.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for tool_utilities namespace + functions
 * Copyright       : 2016 CSCI3081 Group Bits Please
 * Creation Date   : 10/14/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

namespace tool_utilities {
    void createCircle(double** mask, int height, int width, double radius);
    void fillMask(double** mask, int height, int width, double opacity);
}

#endif  // INCLUDE_TOOL_UTILITIES_H_
