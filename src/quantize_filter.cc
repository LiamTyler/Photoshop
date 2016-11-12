/*******************************************************************************
 * Name            : quantize_filter.cc
 * Project         : FlashPhotoApp
 * Module          : Quantize Filter
 * Description     : CC of Quantize Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/11/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "include/quantize_filter.h"
#include <math.h>
#include <string>
#include <iostream>
#include <iomanip>
#include "include/tool_utilities.h"

QuantizeFilter::QuantizeFilter(int bins) : bins_(bins) {}

QuantizeFilter::~QuantizeFilter() {}

float QuantizeFilter::ApplyToColor(std::string color,
                                   const ColorData& current) {
    float c;
    if (color == "red")
        c = current.red();
    else if (color == "green")
        c = current.green();
    else if (color == "blue")
        c = current.blue();
    else
        std::cerr << "WRONG COLOR INPUT" << std::endl;

    float delta = 1.0 / (bins_ - 1);

    return round(c / delta) / static_cast<float>(bins_ - 1);
}
