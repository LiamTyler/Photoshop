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
#include "lib/libimgtools/src/include/color_data.h"
#include <cmath>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

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

float ColorData::get_red() const {
    return red_;
}

float ColorData::get_green() const {
    return green_;
}

float ColorData::get_blue() const {
    return blue_;
}

float ColorData::get_alpha() const {
    return alpha_;
}

// ColorData ColorData::clamped_color(void) const {
//        float clamped_red = ColorData::clamp_value(this->red(), 0.f, 1.f);
//        float clamped_green = ColorData::clamp_value(this->green(), 0.f, 1.f);
//        float clamped_blue = ColorData::clamp_value(this->blue(), 0.f, 1.f);
//        float clamped_alpha = ColorData::clamp_value(this->alpha(), 0.f, 1.f);
//
//        return ColorData(clamped_red, clamped_green,
//                         clamped_blue, clamped_alpha);
// }

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

bool operator== (const ColorData& a, const ColorData& b) {
    return a.red_ == b.red_ && a.green_ == b.green_ &&
           a.blue_ == b.blue_ && a.alpha_ == b.alpha_;
}

bool operator!= (const ColorData& a, const ColorData& b) {
    // If a pixel is within 1 / 256 they are the same really
    float delta = 1.0 / 256;
    float dr = abs(a.red_ - b.red_);
    float dg = abs(a.green_ - b.green_);
    float db = abs(a.blue_ - b.blue_);
    bool t = (dr < delta && dg < delta && db < delta);
    /*
    if (t) {
        cout << "a red = " << a.red_ << ", b red = " << b.red_ << endl;
        cout << "a green = " << a.green_ << ", b green = " << b.green_ << endl;
        cout << "a blue = " << a.blue_ << ", b blue = " << b.blue_ << endl;
        cout << "a alpha = " << a.alpha_ << ", b alpha = " << b.alpha_ << endl;
    }
    */
    return t;
}

std::ostream& operator<<(std::ostream& out, const ColorData& b) {
    out << "(" << b.red_ << "," << b.green_ << "," << b.blue_ << ")";
    return out;
}

}  /* namespace image_tools */
