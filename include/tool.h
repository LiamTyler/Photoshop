#ifndef INCLUDE_TOOL_H_
#define INCLUDE_TOOL_H_

#include "include/color_data.h"
#include "include/pixel_buffer.h"

class Tool {
    public:
        Tool(int width, int height);
        Tool();
        ~Tool();
        void applyTool(image_tools::PixelBuffer* buff, image_tools::ColorData current_color, int x, int y);
    private:
        int width_;
        int height_;
        double** mask_;
};

#endif
