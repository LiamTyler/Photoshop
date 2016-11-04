/*******************************************************************************
 * Name            : pixel_buffer.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for PixelBuffer class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_PIXEL_BUFFER_H_
#define SRC_INCLUDE_PIXEL_BUFFER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include "include/color_data.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Stores an array of ColorData, such as an image that can be drawn to
 * the screen.
 * In this class, (0,0) is the top left corner of the screen/image, which is the
 * not the same as the coordinate system defined by GLUT, where (0,0) is the
 * bottom left corner of the screen. Your implementation will need to account
 * for this.
 */
class PixelBuffer {
 public:
  PixelBuffer(int w, int h, ColorData background_color);
  PixelBuffer(const PixelBuffer&rhs);
  virtual ~PixelBuffer(void) {}

  PixelBuffer& operator=(const PixelBuffer &rhs);

  /**
   * @brief Set the value for a pixel within the buffer/on the screen
   */
  void set_pixel(int x, int y, const ColorData& color);

  inline ColorData const *data(void) const { return &pixels_[0]; }
  inline int height(void) const { return height_; }
  inline int width(void) const { return width_; }

  /**
   * @brief Get the background color that was used to initialize the PixelBuffer
   * @return The background color
   */
  const ColorData& background_color(void) const { return background_color_; }

  /**
   * @brief Get the color of a specific pixel
   * @return The color associated with a specific pixel
   */
  ColorData get_pixel(int x, int y) const;

 private:
  const int width_; /**< X dimension--cannot be changed  */
  const int height_; /**< Y dimension--cannot be changed  */

  std::vector<ColorData> pixels_; /**< Raw pixel data */
  ColorData background_color_; /** Color used to initialize the pixel buffer */
};

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_PIXEL_BUFFER_H_ */
