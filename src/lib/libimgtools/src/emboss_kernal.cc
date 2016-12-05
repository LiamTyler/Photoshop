/*******************************************************************************
 * Name            : emboss_kernal.cc
 * Project         : FlashPhotoApp
 * Module          : EmbossKernal
 * Description     : CC of EmbossKernal
 * Copyright       : Group Bits Please
 * Creation Date   : 11/17/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "lib/libimgtools/src/include/emboss_kernal.h"
#include <iostream>

EmbossKernal::EmbossKernal() : Kernal(3, 3) {
    InitializeKernal();
}

void EmbossKernal::InitializeKernal() {
    int width = get_width();
    int height = get_height();
    float** kern = get_kernal();

    // Create a kernal that will give the image a shadowy, etched look
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            // Set values in the upper left corner of the kernal
            // to -1
            if (c < r) {
                kern[r][c] = -1.0;
            // Set values in the lower right corner of the kernal
            // to 1
            } else if (r < c) {
                kern[r][c] = 1.0;
            // Set values along the diagonal to 0
            } else {
                kern[r][c] = 0;
            }
        }
    }
}
