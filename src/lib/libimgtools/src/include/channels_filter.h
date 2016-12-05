/*******************************************************************************
 * Name            : channels_filter.h
 * Project         : FlashPhotoApp
 * Module          : Channels Filter
 * Description     : Header of Channels Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/12/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_CHANNELS_FILTER_H_
#define SRC_INCLUDE_CHANNELS_FILTER_H_

#include <string>
#include "lib/libimgtools/src/include/simple_filter.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

class ChannelsFilter : public SimpleFilter {
 public:
  ChannelsFilter(float red_channel, float green_channel,
                        float blue_channel);
  ~ChannelsFilter();
  float ApplyToColor(std::string, const ColorData& current);
  std::string name(void) { return "Channels"; }

 private:
  float red_channel_;
  float green_channel_;
  float blue_channel_;
};

#endif  // SRC_INCLUDE_CHANNELS_FILTER_H_
