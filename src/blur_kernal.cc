/*******************************************************************************
 * Name            : blur_kernal.cc
 * Project         : FlashPhotoApp
 * Module          : BlurKernal
 * Description     : CC of BlurKernal
 * Copyright       : Group Bits Please
 * Creation Date   : 11/16/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "include/blur_kernal.h"
#include "include/tool_utilities.h"

BlurKernal::BlurKernal(int amount) : Kernal(amount / 2 * 2 + 1,
                                            amount / 2 * 2 + 1),
                                     amount_(amount / 2 * 2 + 1) {
    InitializeKernal();
}

BlurKernal::BlurKernal() : Kernal(),
                           amount_(-1) {}

void BlurKernal::InitializeKernal() {
    int width = get_width();
    int height = get_height();
    float** kern = get_kernal();
    tool_utilities::CreateCircle(kern, height, width,
                                 static_cast<float>(width / 2));

    // Find out how many pixels there are in the circle
    int total = 0;
    for (int r = 0; r < height; r++)
        for (int c = 0; c < width; c++)
            total += kern[r][c];

    // Go through and assign the percent we want to the pixels that are
    // in the circle radius
    double percent = 1 / static_cast<double>(total);
    for (int r = 0; r < height; r++)
        for (int c = 0; c < width; c++)
            if (kern[r][c] > 0)
                kern[r][c] = percent;
    /*
    for (int r = 0; r < height; r++) { 
        for (int c = 0; c < width; c++) {
            std::cout << kern[r][c] << " ";
        }
        std::cout << std::endl;
    }
    */
}
