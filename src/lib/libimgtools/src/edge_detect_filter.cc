/*******************************************************************************
 * Name            : edge_detect_filter.cc
 * Project         : FlashPhotoApp
 * Module          : Edge Detect Filter
 * Description     : CC of Edge Detect Filter
 * Copyright       : Group Bits Please
 * Creation Date   : 11/11/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#include "lib/libimgtools/src/include/edge_detect_filter.h"
#include "lib/libimgtools/src/include/edge_detect_kernal.h"

EdgeDetectFilter::EdgeDetectFilter() : KernalFilter(new EdgeDetectKernal()) {}
