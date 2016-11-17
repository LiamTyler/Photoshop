/*******************************************************************************
 * Name            : kernal.cc
 * Project         : FlashPhotoApp
 * Module          : Parent Kernal class
 * Description     : CC of Kernal class
 * Copyright       : Group Bits Please
 * Creation Date   : 11/13/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "include/kernal.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include "include/pixel_buffer.h"
#include "include/color_data.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

Kernal::Kernal(int width, int height) : width_(width),
                                        height_(height),
                                        kernal_(nullptr) {
    AllocateKernal(width, height);
}

Kernal::~Kernal() {
    DeallocateKernal();
}

void Kernal::Resize(int width, int height) {
    DeallocateKernal();
    AllocateKernal(width, height);
    InitializeKernal();
}

void Kernal::ApplyKernal(PixelBuffer* oldimage, PixelBuffer* newimage,
                               int start_x, int start_y) {
    int buff_width = oldimage->width();
    int buff_height = oldimage->height();
    int kern_mid_x = width_ / 2;
    int kern_mid_y = height_ / 2;
    ColorData total;

    total = ColorData(0, 0, 0);
    // Center the kernal over the pixel, and apply it by
    // getting the running total of pixel * intensity
    for (int kr = height_ - 1; kr >= 0; kr--) {
        for (int kc = 0; kc < width_; kc++) {
            int cur_x = start_x + kc - kern_mid_x;
            int cur_y = start_y + (height_ - 1) - kr - kern_mid_y;
            if (0 <= cur_x && cur_x < buff_width &&
                0 <= cur_y && cur_y < buff_height) {
                total = total + oldimage->get_pixel(cur_x, cur_y)
                                * kernal_[kr][kc];
            } else {
                total = total +
                        oldimage->get_pixel(
                        std::min(buff_width - 1, std::max(0, cur_x)),
                        std::min(buff_height - 1, std::max(0, cur_y)))
                        * kernal_[kr][kc];
            }
        }
    }
    // total = total* (height_ * width_ / applied);
    newimage->set_pixel(start_x, start_y, total.clamped_color() );
    // std::cout << "Pixel at (" << r << "," << c << "): "
    // << total.clamped_color() << std::endl;
}

void Kernal::AllocateKernal(int width, int height) {
    // If kernal already exists, delete it
    if (kernal_ != nullptr) {
        DeallocateKernal();
    }
    // Allocate new kernal
    width_ = width;
    height_ = height;
    // TODO(tyler147): Make this faster by using a single new
    kernal_ = new float*[height_];
    for (int h = 0; h < height_; h++)
        kernal_[h] = new float[width_]();
}

void Kernal::DeallocateKernal() {
    if (kernal_ == nullptr)
        return;
    for (int h = 0; h < height_; h++)
        delete[] kernal_[h];
    delete[] kernal_;
    width_ = 0;
    height_ = 0;
    kernal_ = nullptr;
}
