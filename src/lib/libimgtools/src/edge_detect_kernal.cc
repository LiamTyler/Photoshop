/*******************************************************************************
 * Name            : edge_detect_kernal.cc
 * Project         : FlashPhotoApp
 * Module          : EdgeDetectKernal
 * Description     : CC of EdgeDetectKernal
 * Copyright       : Group Bits Please
 * Creation Date   : 11/16/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "lib/libimgtools/src/include/edge_detect_kernal.h"

EdgeDetectKernal::EdgeDetectKernal() : Kernal(3, 3) {
    InitializeKernal();
}

void EdgeDetectKernal::InitializeKernal() {
    int width = get_width();
    int height = get_height();
    float** kern = get_kernal();
    int center_width = width/2;
    int center_height = height/2;
    float total = static_cast<float>((width * height) - 1);


    // Set all outer positions of the kernal to -1, set the
    // center to the value that will make all values in the
    // kernal add to 0
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
