/*******************************************************************************
 * Name            : channels_filter.cc
 * Project         : FlashPhotoApp
 * Module          : Channels Filter
 * Description     : CC of Channels Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/12/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "lib/libimgtools/src/include/channels_filter.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "lib/libimgtools/src/include/tool_utilities.h"

ChannelsFilter::ChannelsFilter(float red_channel, float green_channel,
                            float blue_channel) : red_channel_(red_channel),
                                                green_channel_(green_channel),
                                                blue_channel_(blue_channel) {}

ChannelsFilter::~ChannelsFilter() {}

float ChannelsFilter::ApplyToColor(std::string color,
                                   const ColorData& current) {
    float c;
    // Multiply the current color by the value passed in for
    // that color's channel
    if (color == "red")
        c = current.red() * red_channel_;
    else if (color == "green")
        c = current.green() * green_channel_;
    else if (color == "blue")
        c = current.blue() * blue_channel_;
    else
        std::cerr << "WRONG COLOR INPUT" << std::endl;

    return c;
}
