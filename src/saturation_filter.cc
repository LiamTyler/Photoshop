/*******************************************************************************
 * Name            : saturation_filter.cc
 * Project         : FlashPhotoApp
 * Module          : Saturation Filter
 * Description     : CC of Saturation Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/17/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "include/saturation_filter.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "include/tool_utilities.h"

using image_tools::ColorData;

SaturationFilter::SaturationFilter(float amount) : amount_(amount) {}

SaturationFilter::~SaturationFilter() {}

float SaturationFilter::ApplyToColor(std::string color,
                                   const ColorData& current) {
    float c;
    float lum;
    lum = current.luminance();
    float value;

    if (amount_ == 0) {
        value = 0;
    } else {
        // Calculate amount of current color to be applied
        value = 1.0/amount_;
    }

    if (color == "red")
        c = (lum * value) + (current.red() * (1.0 - value));
    else if (color == "green")
        c = (lum * value) + (current.green() * (1.0 - value));
    else if (color == "blue")
        c = (lum * value) + (current.blue() * (1.0 - value));
    else
        std::cerr << "WRONG COLOR INPUT" << std::endl;

    return c;
}
