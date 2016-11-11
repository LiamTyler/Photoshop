/*******************************************************************************
 * Name            : filter.cc
 * Project         : FlashPhotoApp
 * Module          : Parent Filter class
 * Description     : CC of Filter class
 * Copyright       : Group Bits Please
 * Creation Date   : 11/10/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include <string>
#include "include/filter.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

Filter::Filter() : width_(0),
                   height_(0),
                   kernal_(nullptr) {}

Filter::Filter(int width, int height) : width_(width),
                                        height_(height),
                                        kernal_(nullptr) {
    AllocateKernal(width, height);
}

Filter::~Filter() {
    DeallocateKernal();
}

void Filter::CreateKernal(int width, int height) {
    DeallocateKernal();
    AllocateKernal(width, height);
    InitializeKernal();
}

void Filter::ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage) {
    int buff_height = oldimage->height();
    int buff_width = oldimage->width();
    ColorData total = ColorData();
    int kern_mid_x = width_ / 2;
    int kern_mid_y = height_ / 2;

    for (int r = 0; r < buff_height; r++) {
        for (int c = 0; c < buff_width; c++) {
            total = ColorData();
            // Center the kernal over the pixel, and apply it by
            // getting the running total of pixel * intensity
            for (int kr = 0; kr < height_; kr++) {
                for (int kc = 0; kc < width_; kc++) {
                    int cur_x = c - kern_mid_x + kc;
                    int cur_y = r - kern_mid_y + kr;
                    if (0 <= cur_x && cur_x < buff_width &&
                        0 <= cur_y && cur_y < buff_height)
                        total = total + oldimage->get_pixel(cur_x, cur_y)
                                        * kernal_[kr][kc];
                }
            }
            newimage->set_pixel(c, r, total);
        }
    }
}

void Filter::AllocateKernal(int width, int height) {
    // If kernal already exists, delete it
    if (kernal_ != nullptr) {
        DeallocateKernal();
    }
    // Allocate new kernal
    width_ = width;
    height_ = height;
    // TODO(tyler147): Make this faster by using a single new
    kernal_ = new double*[height_];
    for (int h = 0; h < height_; h++)
        kernal_[h] = new double[width_];
}

void Filter::DeallocateKernal() {
    if (kernal_ == nullptr)
        return;
    for (int h = 0; h < height_; h++)
        delete[] kernal_[h];
    delete[] kernal_;
    width_ = 0;
    height_ = 0;
    kernal_ = nullptr;
}