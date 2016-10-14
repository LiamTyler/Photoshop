#include "include/tool_utilities.h"
#include <cmath>

namespace tool_utilities {

    void createCircle (double** mask, int height, int width, double radius) {
        int cent_x = width / 2;
        int cent_y = height / 2;
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                if (pow(w - cent_x, 2) + pow(h - cent_y, 2) <= radius * radius) {
                    mask[h][w] = 1.0; 
                }
            }
        }
    }

}  // namespace tool_utilities
