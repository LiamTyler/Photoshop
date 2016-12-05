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

#include <iostream>

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
  inline ColorData clamped_color(void) const {
        float clamped_red = ColorData::clamp_value(this->red(), 0.f, 1.f);
        float clamped_green = ColorData::clamp_value(this->green(), 0.f, 1.f);
        float clamped_blue = ColorData::clamp_value(this->blue(), 0.f, 1.f);
        float clamped_alpha = ColorData::clamp_value(this->alpha(), 0.f, 1.f);

        return ColorData(clamped_red, clamped_green,
                         clamped_blue, clamped_alpha);
  }

  float get_red() const;
  float get_green() const;
  float get_blue() const;
  float get_alpha() const;

  /*
   * Arithmetic operators (friends so that non-member functions can access
   * private variables)
   */
  friend ColorData operator* (const ColorData& a, float f);
  friend ColorData operator+ (const ColorData& a, const ColorData& b);
  friend ColorData operator- (const ColorData& a, const ColorData& b);
  friend std::ostream& operator<<(std::ostream& out, const ColorData& c);

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
