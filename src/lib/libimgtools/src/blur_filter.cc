/*******************************************************************************
 * Name            : blur_filter.cc
 * Project         : FlashPhotoApp
 * Module          : Blur Filter
 * Description     : CC of Blur Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/11/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "lib/libimgtools/src/include/blur_filter.h"
#include "lib/libimgtools/src/include/blur_kernal.h"
#include "lib/libimgtools/src/include/tool_utilities.h"

BlurFilter::BlurFilter(int amount) : KernalFilter(new BlurKernal(amount)) {}
