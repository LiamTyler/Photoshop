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

    CopyPixelBuffer(image_, buff, x, buff->height() - y);
}

void TStamp::LoadImage(PixelBuffer* l_img) {
    if (image_ != nullptr)
        delete image_;

    image_ = l_img;
    set_height(image_->height());
    set_width(image_->width());
}
