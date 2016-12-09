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

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CHANNELS_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CHANNELS_FILTER_H_

#include <string>
#include "lib/libimgtools/src/include/simple_filter.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

/**
 * @brief Scale each of the RGB channels by a specified amount from the user.
 *
 */
class ChannelsFilter : public SimpleFilter {
 public:
  ChannelsFilter(float red_channel, float green_channel,
                        float blue_channel);
  ~ChannelsFilter();
  float ApplyToColor(std::string, const ColorData& current);
  std::string name(void) { return "Channels"; }

 private:
  float red_channel_;  /**<Red scaling factor  */
  float green_channel_;  /**<Green scaling factor  */
  float blue_channel_;  /** Blue scaling factor  */
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CHANNELS_FILTER_H_
