/*******************************************************************************
 * Name            : color_data.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of ColorData class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/color_data.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
ColorData::ColorData(void)
    : red_(1), green_(1), blue_(1), alpha_(1) {}
ColorData::ColorData(float r, float g, float b)
    : red_(r), green_(g), blue_(b), alpha_(1) {}
ColorData::ColorData(float r, float g, float b, float a)
    : red_(r), green_(g), blue_(b), alpha_(a)  {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float ColorData::luminance(void) const {
    return static_cast<float>(0.2126)*red_ +
        static_cast<float>(0.7152)*green_ +
        static_cast<float>(0.0722)*blue_;
}

ColorData ColorData::clamped_color(void) const {
        float clamped_red = ColorData::clamp_value(this->red(), 0.f, 1.f);
        float clamped_green = ColorData::clamp_value(this->green(), 0.f, 1.f);
        float clamped_blue = ColorData::clamp_value(this->blue(), 0.f, 1.f);
        float clamped_alpha = ColorData::clamp_value(this->alpha(), 0.f, 1.f);

        return ColorData(clamped_red, clamped_green,
                         clamped_blue, clamped_alpha);
}

// Apply component-wise arithmatic operations
ColorData operator* (const ColorData& a, float f) {
    return ColorData(a.red_*f, a.green_*f, a.blue_*f, a.alpha_*f);
}

ColorData operator+ (const ColorData& a, const ColorData& b) {
        return ColorData(a.red_ + b.red_, a.green_ + b.green_,
                         a.blue_ + b.blue_, a.alpha_ + b.alpha_);
}

ColorData operator- (const ColorData& a, const ColorData& b) {
        return ColorData(a.red_ - b.red_, a.green_ - b.green_,
                         a.blue_ - b.blue_, a.alpha_ - b.alpha_);
}

}  /* namespace image_tools */
