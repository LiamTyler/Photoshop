#ifndef SRC_INCLUDE_TOOL_UTILITIES_H_
#define SRC_INCLUDE_TOOL_UTILITIES_H_

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
    void CreateCircle(float** mask, int height, int width, float radius);
    void FillMask(float** mask, int height, int width, float opacity);
}

#endif  // SRC_INCLUDE_TOOL_UTILITIES_H_
