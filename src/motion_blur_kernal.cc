/*******************************************************************************
 * Name            : motion_blur_kernal.cc
 * Project         : FlashPhotoApp
 * Module          : MotionBlurKernal
 * Description     : CC of MotionBlurKernal
 * Copyright       : Group Bits Please
 * Creation Date   : 11/16/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "include/motion_blur_kernal.h"

MotionBlurKernal::MotionBlurKernal(int amount, int direction) :
                                   Kernal(amount * 2 + 1,
                                          amount * 2 + 1),
                                   amount_(amount * 2 + 1),
                                   direction_(direction) {
    InitializeKernal();
}

MotionBlurKernal::MotionBlurKernal() : amount_(-1),
                                       direction_(-1) {}

void MotionBlurKernal::InitializeKernal() {
    int width = get_width();
    int mid_w = width / 2;
    int height = get_height();
    int mid_h = height / 2;
    float** kern = get_kernal();

    double percent = 1 / static_cast<double>(width);
    // If N_S
    if (direction_ == 0) {
        for (int r = 0; r < height; r++)
            kern[r][mid_w] = percent;
    } else if (direction_ == 1) {  // If E_W
        for (int c = 0; c < width; c++)
            kern[mid_h][c] = percent;
    } else if (direction_ == 2) {  // If NE_SW
        for (int r = 0; r < height; r++)
            kern[height - r - 1][r] = percent;
    } else {  // If NW_SE
        for (int r = 0; r < height; r++)
            kern[r][r] = percent;
    }
}
