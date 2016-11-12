/*******************************************************************************
 * Name            : motion_blur_filter.cc
 * Project         : FlashPhotoApp
 * Module          : MotionBlur Filter
 * Description     : CC of MotionBlur Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/13/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "include/motion_blur_filter.h"
#include <string>
#include "include/tool_utilities.h"

MotionBlurFilter::MotionBlurFilter(float amount, int direction) :
                       KernalFilter(static_cast<int>(amount),
                                    static_cast<int>(amount)),
                       amount_(amount),
                       direction_(direction) {
                           CreateKernal(static_cast<int>(amount),
                                        static_cast<int>(amount));
}

void MotionBlurFilter::InitializeKernal() {
    int width = get_width();
    int mid_w = width / 2;
    int height = get_height();
    int mid_h = height / 2;
    float** kern = get_kernal();

    // If N_S
    if (direction_ == 0) {
        for (int r = 0; r < height; r++)
            kern[r][mid_w] = 1.0;
    } else if (direction_ == 1) {  // If E_W
        for (int c = 0; c < width; c++)
            kern[mid_h][c] = 1.0;
    } else if (direction_ == 2) {  // If NE_SW
        for (int r = 0; r < height; r++)
            kern[height - r - 1][r] = 1.0;
    } else {  // If NW_SE
        for (int r = 0; r < height; r++)
            kern[r][r] = 1.0;
    }

    // Find out how many pixels there
    double total = 0;
    for (int r = 0; r < height; r++)
        for (int c = 0; c < width; c++)
            total += kern[r][c];

    // Go through and assign the percent we want to the pixels that are 1.0
    double percent = 1 / static_cast<double>(total);
    for (int r = 0; r < height; r++)
        for (int c = 0; c < width; c++)
            if (kern[r][c] > 0)
                kern[r][c] = percent;
}
