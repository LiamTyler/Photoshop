/*******************************************************************************
 * Name            : stamp.cc
 * Project         : BrushWork
 * Module          : tools
 * Description     : CC file for the TStamp
 * Copyright       : 2016 CSCI3081W Group Bits Please
 * Creation Date   : 11/20/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "include/stamp_tool.h"
#include "include/tool_utilities.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;
using tool_utilities::CopyPixelBuffer;

TStamp::TStamp() : Tool(1, 1),
                   image_(nullptr) {}

TStamp::~TStamp() {
    if (image_)
        delete image_;
}


void TStamp::ApplyTool(PixelBuffer* buff, ColorData current_color,
                        int x, int y, int last_x, int last_y) {
    if (image_ == nullptr || last_x != -1 || last_y != -1)
        return;

    // CopyPixelBuffer(image_, buff, x, buff->height() - y);

    int f_w = image_->width();
    int f_half_w = f_w / 2;
    int f_h = image_->height();
    int f_half_h = f_h / 2;
    int t_width = buff->width();
    int t_height = buff->height();

    // Copy the actual pixels over into the buffer, now that it has the
    // correct size and bg color
    for (int r = 0; r < f_h; r++) {
        for (int c = 0; c < f_w; c++) {
            int nx = c + x - f_half_w;
            int ny = r + t_height - y - f_half_h;
            if (0 <= nx && nx < t_width && 0 <= ny && ny < t_height &&
                    image_->get_pixel(c, r).get_alpha() != 0)
                buff->set_pixel(nx, ny, image_->get_pixel(c, r));
        }
    }
}

void TStamp::LoadImage(PixelBuffer* l_img) {
    if (image_ != nullptr)
        delete image_;

    image_ = l_img;
    set_height(image_->height());
    set_width(image_->width());
}
