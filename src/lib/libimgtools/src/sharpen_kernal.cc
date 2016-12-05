/*******************************************************************************
 * Name            : sharpen_kernal.cc
 * Project         : FlashPhotoApp
 * Module          : SharpenKernal
 * Description     : CC of SharpenKernal
 * Copyright       : Group Bits Please
 * Creation Date   : 11/16/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "lib/libimgtools/src/include/sharpen_kernal.h"

SharpenKernal::SharpenKernal(int amount) : Kernal(3, 3),
                                           amount_(amount) {
    InitializeKernal();
}

void SharpenKernal::InitializeKernal() {
    int width = get_width();
    int height = get_height();
    float** kern = get_kernal();
    int center_width = width/2;
    int center_height = height/2;
    // increase the value for the center of the kernal based on the amount
    float total = static_cast<float>((width * height) - 1 + (amount_ / 2));

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            // If any amount was selected, set all outer positions in the
            // kernal to -1 and the center position to total
            if (amount_ != 0) {
                if (r == center_height && c == center_width) {
                    kern[r][c] = total;
                } else {
                    kern[r][c] = -1.0;
                }
            // If 0 was selected as the amount, set the kernal to the
            // identity so the image remains unchanged
            } else {
                if (r == center_height && c == center_width) {
                    kern[r][c] = 1;
                } else {
                    kern[r][c] = 0;
                }
            }
        }
    }
}
