#include "include/tool.h"
#include "include/tool_utilities.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using image_tools::PixelBuffer;
using image_tools::ColorData;

Tool::Tool(int width, int height) {
    width_ = width;
    height_ = height;

    // Allocate the memory for the 2d mask with height rows and width columns
    mask_ = new double*[height];
    for(int i = 0; i < height; i++) {
        mask_[i] = new double[width];
    }

    tool_utilities::createCircle(mask_, height_, width_, static_cast<double>(width) / 2);
}

Tool::Tool() : Tool(120,120) {}

Tool::~Tool() {
    for(int i = 0; i < height_; i++) {
        delete[] mask_[i];
    }
    delete[] mask_;
}

void Tool::applyTool(PixelBuffer* buff, ColorData current_color, int x, int y) {
   int mid_x = width_ / 2;
   int mid_y = height_ / 2;
   int screen_h = buff->height();
   int screen_w = buff->width();

   for(int step_x = 0; step_x < width_; step_x++) {
       for(int step_y = 0; step_y < height_; step_y++) {
           int cur_x = x + step_x - mid_x;
           // Needs to be buff->height() - y because pixels buffer's 0,0 is the lower left
           // corner, while in brushwork, 0,0 is the upper left
           int cur_y = screen_h - (y + step_y - mid_y);
           if(cur_x >= 0 && cur_x < screen_w && cur_y >= 0 && cur_y < screen_h) {
               double intensity = mask_[step_x][step_y];
               //TODO: copy constructor
               buff->set_pixel(cur_x, cur_y, current_color * intensity + buff->get_pixel(cur_x, cur_y) * (1.0 - intensity));
           }
       }
   }
}
