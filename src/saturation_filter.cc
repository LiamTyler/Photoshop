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

    // Find the luminance of the current color, set the new color
    // to a combination of some amount of the luminance and some
    // amount of the current color, based on amount_
    if (color == "red")
        c = (lum * (1.0 - amount_)) + (current.red() * amount_);
    else if (color == "green")
        c = (lum * (1.0 - amount_)) + (current.green() * amount_);
    else if (color == "blue")
        c = (lum * (1.0 - amount_)) + (current.blue() * amount_);
    else
        std::cerr << "WRONG COLOR INPUT" << std::endl;

    return c;
}
