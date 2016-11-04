/*******************************************************************************
 * Name            : color_data.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for ColorData class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_COLOR_DATA_H_
#define SRC_INCLUDE_COLOR_DATA_H_

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This color data class stores color in floating point format.
 * The Red, Green, Blue, and Alpha channels range from 0.0 to 1.0.
 */
class ColorData {
 public:
  ColorData(void);
  ColorData(float r, float g, float b);
  ColorData(float r, float g, float b, float a);

  inline void red(float r) { red_ = r; }
  inline void green(float g) { green_ = g; }
  inline void blue(float b) { blue_ = b; }
  inline void alpha(float a) { alpha_ = a; }
  inline float red(void) const { return red_; }
  inline float green(void) const { return green_; }
  inline float blue(void) const { return blue_; }
  inline float alpha(void) const { return alpha_;}

  /**
   * @brief Get the "brightness" of the color according to a perceptual metric
   * that weights the red, green, and blue components of the color
   * non-uniformly.
   */
  float luminance(void) const;

  /**
   * @brief Return a clamped version of a ColorData instance
   * All colors and the alpha value are restricted to [0.0,1.0]
   */
  inline ColorData clamped_color(void) const;

  /*
   * Arithmetic operators (friends so that non-member functions can access
   * private variables)
   */
  friend ColorData operator* (const ColorData& a, float f);
  friend ColorData operator+ (const ColorData& a, const ColorData& b);
  friend ColorData operator- (const ColorData& a, const ColorData& b);

 private:
  static inline float clamp_value(float input, float a, float b)
  { return input < a ? a : (input > b ? b : input);}

  float red_;
  float green_;
  float blue_;
  float alpha_;
};

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_COLOR_DATA_H_ */
