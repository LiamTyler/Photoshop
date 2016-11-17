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

#include "include/blur_filter.h"
#include "include/blur_kernal.h"
#include "include/tool_utilities.h"

BlurFilter::BlurFilter(int amount) : KernalFilter(new BlurKernal(amount)) {}
