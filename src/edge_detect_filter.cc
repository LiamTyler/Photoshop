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

#include <string>
#include "include/edge_detect_filter.h"
#include "include/tool_utilities.h"

EdgeDetectFilter::EdgeDetectFilter() :
                       KernalFilter(3, 3) {
    CreateKernal(3, 3);
}

EdgeDetectFilter::~EdgeDetectFilter() {}

void EdgeDetectFilter::InitializeKernal() {
    int width = get_width();
    int height = get_height();
    float** kern = get_kernal();
    int center_width = width/2;
    int center_height = height/2;
    float total = static_cast<float>((width * height) - 1);

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            if (r == center_height && c == center_width) {
                kern[r][c] = total;
            } else {
                kern[r][c] = -1.0;
            }
        }
    }
}
