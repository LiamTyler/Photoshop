/*******************************************************************************
 * Name            : blur_filter.cc
 * Project         : FlashPhotoApp
 * Module          : Blur Filter
 * Description     : CC of Blur Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/11/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "include/blur_filter.h"
#include <string>
#include "include/tool_utilities.h"

BlurFilter::BlurFilter(float amount) :
                       KernalFilter(static_cast<int>(amount),
                                    static_cast<int>(amount)),
                       amount_(amount) {
                           CreateKernal(static_cast<int>(amount),
                                        static_cast<int>(amount));
                       }

BlurFilter::BlurFilter() : amount_(0.0) {}

BlurFilter::~BlurFilter() {}

void BlurFilter::InitializeKernal() {
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
}
