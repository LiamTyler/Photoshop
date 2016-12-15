/*******************************************************************************
 * Name            : stamp_tool.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Header of TStamp
 * Copyright       : Group Bits Please
 * Creation Date   : 11/20/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_STAMP_TOOL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_STAMP_TOOL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/tool.h"

using image_tools::PixelBuffer;

/**
 * @brief A stamp tool that is meant to be applied in a "click" rather than
 * "click and drag" motion like all the other canvas tools. It can stamp images
 * of any size onto the canvas. The stamp image must be explicitly set after
 * initializing the stamp tool.
 *
 */
class TStamp : public Tool {
 public:
  TStamp();
  virtual ~TStamp();
  /**
   * @brief Loads an image into the stamp tool
   *
   */
  void LoadImage(PixelBuffer* l_img);
  void ApplyTool(PixelBuffer* buff,
    image_tools::ColorData current_color, int x, int y, int last_x, int last_y);
  std::string name(void) { return "Stamp"; }
 private:
  TStamp(const TStamp& t) = delete;
  TStamp& operator=(const TStamp& t) = delete;
  PixelBuffer* image_;  //< The image being stamped down
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_STAMP_TOOL_H_
