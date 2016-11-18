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

#include "include/emboss_kernal.h"
#include <iostream>

EmbossKernal::EmbossKernal() : Kernal(3, 3) {
    InitializeKernal();
}

void EmbossKernal::InitializeKernal() {
    int width = get_width();
    int height = get_height();
    float** kern = get_kernal();
    int center_width = width/2;
    int center_height = height/2;

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            if (c < r) {
                kern[r][c] = -1.0;
            } else if (r < c) {
                kern[r][c] = 1.0;
            } else {
                kern[r][c] = 0;
            }
        }
    }
//    for (int r = height - 1; r >= 0; r--) {
//        for (int c = 0; c < width; c++) {
//            std::cout << kern[r][c] << " ";
//        }
//        std::cout << "" << std::endl;
//    }
}
