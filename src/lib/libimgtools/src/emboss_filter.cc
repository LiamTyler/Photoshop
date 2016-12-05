/*******************************************************************************
 * Name            : emboss_filter.cc
 * Project         : FlashPhotoApp
 * Module          : Emboss Filter
 * Description     : CC of Emboss Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/17/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "lib/libimgtools/src/include/emboss_filter.h"
#include "lib/libimgtools/src/include/emboss_kernal.h"

EmbossFilter::EmbossFilter() : KernalFilter(new EmbossKernal()) {}
