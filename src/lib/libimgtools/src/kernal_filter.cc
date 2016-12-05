/*******************************************************************************
 * Name            : filter_filter.cc
 * Project         : FlashPhotoApp
 * Module          : Parent KernalFilter class
 * Description     : CC of KernalFilter class
 * Copyright       : Group Bits Please
 * Creation Date   : 11/10/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/


#include "lib/libimgtools/src/include/kernal_filter.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/color_data.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

KernalFilter::KernalFilter(Kernal* kernal) : kernal_(kernal) {}

KernalFilter::~KernalFilter() {
    delete kernal_;
}

void KernalFilter::ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage) {
    int buff_height = oldimage->height();
    int buff_width = oldimage->width();

    for (int r = 0; r < buff_height; r++)
        for (int c = 0; c < buff_width; c++)
            newimage->set_pixel(c, r, kernal_->ApplyKernal(oldimage, c, r));
}
