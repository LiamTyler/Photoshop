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

#include "include/sharpen_kernal.h"

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
    float total = static_cast<float>((width * height) - 1 + amount_);

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            if (r == center_height && c == center_width) {
                kern[r][c] = total;
            } else {
                kern[r][c] = -1.0;
            }
        }
    }
}
