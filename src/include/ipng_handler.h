#ifndef SRC_INCLUDE_IPNGHANDLER_
#define SRC_INCLUDE_IPNGHANDLER_

#include <string>

#include "include/image_handler.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class IPNGHandler : public ImageHandler {
public:
    static PixelBuffer* loadImage(const std::string fileName);
    static bool saveImage(const std::string fileName, const PixelBuffer* bufferToSave);
};

#endif // SRC_INCLUDE_IPNGHANDLER_
