/*******************************************************************************
 * Name            : motion_blur_filter.cc
 * Project         : FlashPhotoApp
 * Module          : MotionBlur Filter
 * Description     : CC of MotionBlur Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/13/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "lib/libimgtools/src/include/motion_blur_filter.h"
#include "lib/libimgtools/src/include/motion_blur_kernal.h"

MotionBlurFilter::MotionBlurFilter(int amount, int direction) :
    KernalFilter(new MotionBlurKernal(amount, direction)) {}
