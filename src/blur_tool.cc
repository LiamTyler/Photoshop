/*******************************************************************************
 * Name            : blur_tool.cc
 * Project         : BrushWork
 * Module          : tools
 * Description     : CC file for the blur_tool
 * Copyright       : 2016 CSCI3081W Group Bits Please
 * Creation Date   : 11/13/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "include/blur_tool.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "include/blur_kernal.h"
#include "include/tool_utilities.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;
using std::cout;
using std::endl;

TBlur::TBlur(int radius) : Tool(2 * radius + 1, 2 * radius + 1),
                           radius_(radius),
                           kernals_(std::vector<BlurKernal>()),
                           scratch_(nullptr) {
    float** mask = get_mask();
    // TODO(tyler147): move all of this out of the constructor
    int center = radius_;
    int diameter = 2 * radius_ + 1;
    for (int h = 0; h < diameter; h++) {
        for (int w = 0; w < diameter; w++) {
            float intensity = 1.0 - sqrt(pow(h - center, 2) +
                                   pow(w - center, 2))/radius_;

            if (intensity > 0) {
                mask[h][w] = static_cast<int>(radius / 2 * intensity);
            } else {
                mask[h][w] = 0.0;
            }
        }
    }

    // Allocate and Create the kernal map. Essentially, the mask created
    // above is a circle where the highest number is in the middle, and
    // it has a linear falloff. The number at each element is the radius
    // of the BlurKernal that is going to be applied to that pixel.
    // The linear falloff makes it so that the middle pixel will be very
    // blurred, while the ones on the edges aren't so much
    std::vector<int> filled(diameter + 1);

    for (int h = 0; h < diameter; h++)
        for (int w = 0; w < diameter; w++)
            filled[static_cast<int>(mask[h][w])] = 1;

    kernals_.push_back(BlurKernal(1));

    for (int i = 1; i < diameter + 1; i++) {
        if (!filled[i])
            kernals_.push_back(BlurKernal(1));
        else
            kernals_.push_back(BlurKernal(i));
    }

    // Allocate the scratch buffer to place our partially blurred
    scratch_ = new PixelBuffer(diameter, diameter, ColorData());
 
    for (int h = 0; h < diameter; h++) {
        for (int w = 0; w < diameter; w++) {
            cout << std::setw(4) << mask[h][w];
        }
        cout << endl;
    }
    /*
    cout << "Printing the kernals..." << endl;
    for (int i = 0; i < diameter + 1; i++) {
        cout << "i = " << i << endl;
        kernals_[i].print(cout);
        cout << endl;
    }
    */
}

TBlur::TBlur() : TBlur(19) {}

TBlur::~TBlur() {
    // Free the scratch buffer
    delete scratch_;
}

void TBlur::ApplyTool(PixelBuffer* buff, ColorData current_color,
                        int x, int y, int last_x, int last_y) {
    int mid_x = radius_;
    int mid_y = radius_;
    int diameter = radius_ * 2 + 1;
    int screen_h = buff->height();
    int screen_w = buff->width();
    float** mask = get_mask();

    for (int step_y = 0; step_y < diameter; step_y++) {
        for (int step_x = 0; step_x < diameter; step_x++) {
            int cur_x = x + step_x - mid_x;
            // Needs to be buff->height() - y because pixels buffer's
            // 0,0 is the lower left
            // corner, while in brushwork, 0,0 is the upper left
            int cur_y = screen_h - (y + step_y - mid_y);
            if (cur_x >= 0 && cur_x < screen_w &&
                cur_y >= 0 && cur_y < screen_h) {
                    int intensity = static_cast<int>(mask[step_y][step_x]);
                    scratch_->set_pixel(step_x, step_y,
                        kernals_[intensity].ApplyKernal(buff, cur_x, cur_y));
            }
        }
    }

    // Copy the scratch back onto the main buffer
    for (int step_y = 0; step_y < diameter; step_y++) {
        for (int step_x = 0; step_x < diameter; step_x++) {
            int cur_x = x + step_x - mid_x;
            int cur_y = screen_h - (y + step_y - mid_y);
            if (cur_x >= 0 && cur_x < screen_w &&
                cur_y >= 0 && cur_y < screen_h) {
                buff->set_pixel(cur_x, cur_y,
                        scratch_->get_pixel(step_x, step_y));
            }
        }
    }
}
