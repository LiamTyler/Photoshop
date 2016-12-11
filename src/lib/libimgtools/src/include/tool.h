/*******************************************************************************
 * Name            : tool.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Header of tool
 * Copyright       : 2016 CSCI3081W Team_Bits_Please. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_H_

#include <string>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Tool is the representation of a particular BrushWork tool.
 * This baseclass is abstract and does not provide a default mask.
 * Tools inherited from this class MUST:\n
 * (1) Provide a name\n
 * (2) Define the mask. You will get an assert error if you do not.\n
 * Inherited classes may optionally override the default color_blend_math().
 */
class Tool {
 public:
  Tool(int width, int height);
  Tool();
  virtual ~Tool();
  /**
   * @brief Default implementation for applying the tool to the PixelBuffer
   *
   * Uses the current_color and last position of the tool being applied
   * (last_x and last_y) to determine how to apply the mask to the
   * buffer.
   *
   * @param buff The buffer of pixels to apply the tool to
   * @param[in] current_color The current color of the tool
   * @param[in] x The x position of where to apply the tool to
   * @param[in] y The y position of where to apply the tool to
   * @param[in] last_x The x position of the last time the tool was applied
   * (only applicable while the mouse is being dragged)
   * @param[in] last_y The y position of the last time the tool was applied
   * (only applicable while the mouse is being dragged)
   *
   * @return None
   */
  virtual void ApplyTool(image_tools::PixelBuffer* buff,
    image_tools::ColorData current_color, int x, int y, int last_x, int last_y);
  /**
   * @brief A function that some child classes will use to update themselves.
   *
   * Currently depricated.
   *
   * @return None
   *
   */
  virtual void UpdateTool(int width, int height) {}
  inline int get_width() { return width_; }
  inline int get_height() { return height_; }
  inline void set_width(int w) { width_ = w; }
  inline void set_height(int h) { height_ = h; }
  /**
   * @brief Get the mask associated with the tool
   * @return The mask
   */
  inline float** get_mask() { return mask_; }
  /**
   * @brief The name of the tool
   * @return
   */
  virtual std::string name(void) = 0;

 private:
  Tool(const Tool &t) = delete;
  Tool& operator=(const Tool &t) = delete;
  void AllocateMask();
  int width_;
  int height_;
  float** mask_;  /**< 2D array of floats representing the mask  */
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_H_
