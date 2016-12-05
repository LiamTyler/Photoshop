/*******************************************************************************
 * Name            : sharpen_filter.cc
 * Project         : FlashPhotoApp
 * Module          : Sharpen Filter
 * Description     : CC of Sharpen Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/12/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "lib/libimgtools/src/include/sharpen_filter.h"
#include "lib/libimgtools/src/include/sharpen_kernal.h"

SharpenFilter::SharpenFilter(int amount) :
    KernalFilter(new SharpenKernal(amount)) {}
