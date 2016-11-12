/*******************************************************************************
 * Name            : sharpen_filter.cc
 * Project         : FlashPhotoApp
 * Module          : Sharpen Filter
 * Description     : CC of Sharpen Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/12/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "include/sharpen_filter.h"
#include <string>
#include "include/tool_utilities.h"

SharpenFilter::SharpenFilter(float amount) :
                       KernalFilter(3, 3),
                       amount_(amount) {
                           CreateKernal(3, 3);
                       }

SharpenFilter::SharpenFilter() : amount_(0.0) {}

SharpenFilter::~SharpenFilter() {}

void SharpenFilter::InitializeKernal() {
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
