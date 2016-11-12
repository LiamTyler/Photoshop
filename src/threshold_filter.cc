/*******************************************************************************
 * Name            : threshold_filter.cc
 * Project         : FlashPhotoApp
 * Module          : Threshold Filter
 * Description     : CC of Threshold Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/12/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include <string>
#include "include/threshold_filter.h"
#include "include/tool_utilities.h"
#include "include/color_data.h"

using image_tools::PixelBuffer;

ThresholdFilter::ThresholdFilter(float level) :
                       level_(level) {}

ThresholdFilter::ThresholdFilter() : level_(0.0) {}

ThresholdFilter::~ThresholdFilter() {}

float ThresholdFilter::ApplyToColor(std::string color,
                             const image_tools::ColorData& current) {
    float newColor;
    if (color == "red") {
        newColor = current.red();
    } else if (color == "green") {
        newColor = current.green();
    } else {
        newColor = current.blue();
    }
    if (newColor < level_) {
        newColor = 0;
    } else {
        newColor = 1;
    }
    return newColor;
}
