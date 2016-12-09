#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_UTILITIES_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_UTILITIES_H_

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

#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

/**
 * @brief namespace that defines helper functions for mostly the tools,
 * and also the history manager
 *
 */
namespace tool_utilities {
    /**
     * @brief Creates a cirle inside a mask
     *
     * Creates a circle of 1's from the center of the mask, with the
     * rest being 0's.
     *
     * @return None
     */
    void CreateCircle(float** mask, int height, int width, float radius);

    /**
     * @brief Sets all elements in the mask to opacity
     *
     * @return None
     */
    void FillMask(float** mask, int height, int width, float opacity);

    /**
     * @brief Copies one pixel buffer onto another
     *
     * Centers the "from" buffer ontot the "to" buffer at the specified
     * x and y coordinates on the "to" buffer, then copies each pixel
     * that is within the "to" buffer's boundaries, onto the "to" buffer.
     *
     * @return None
     */
    void CopyPixelBuffer(PixelBuffer* from, PixelBuffer* to, int x, int y);
}  /* namespace tool_utilities */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_UTILITIES_H_
