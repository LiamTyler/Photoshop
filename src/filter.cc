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
#include <iostream>
#include <iomanip>
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
    std::cout << "Kernal: w = " << width_ << ", h = " << height_ << std::endl;
    InitializeKernal();
    /* Print out kernal to check if the initialize worked
    for (int r = 0; r < height_; r++) {
        for (int c = 0; c < width_; c++) {
            std::cout << kernal_[r][c] << " ";
        }
        std::cout << std::endl;
    }
    */
}

void Filter::ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage) {
    int buff_height = oldimage->height();
    int buff_width = oldimage->width();
    ColorData total;
    ColorData bgc = oldimage->background_color();
    int kern_mid_x = width_ / 2;
    int kern_mid_y = height_ / 2;
    double applied;

    for (int r = 0; r < buff_height; r++) {
        for (int c = 0; c < buff_width; c++) {
            total = ColorData(0, 0, 0);
            applied = 0;
            // Center the kernal over the pixel, and apply it by
            // getting the running total of pixel * intensity
            for (int kr = 0; kr < height_; kr++) {
                for (int kc = 0; kc < width_; kc++) {
                    int cur_x = c - kern_mid_x + kc;
                    int cur_y = r - kern_mid_y + kr;
                    if (0 <= cur_x && cur_x < buff_width &&
                        0 <= cur_y && cur_y < buff_height) {
                            applied += 1;
                        total = total + oldimage->get_pixel(cur_x, cur_y)
                                        * kernal_[kr][kc];
                    }
                }
            }
            // Adjust color if the mask was partially off the edge
            double p = applied / (width_ * height_);
            ColorData adjusted = total + (bgc * (1 / p));
            newimage->set_pixel(c, r, adjusted);
            // std::cout << "Pixel at (" << r << "," << c << "): "
            // << total << std::endl;
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
