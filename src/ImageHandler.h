#ifndef SRC_INCLUDE_IMAGEHANDLER_
#define SRC_INCLUDE_IMAGEHANDLER_

#include <string>
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class ImageHandler {
public:
    enum IMAGE_TYPE {
        PNG_IMAGE,
        JPG_IMAGE,
        UNKNOWN_IMAGE
    };

    static PixelBuffer* loadImage(const std::string & fileName);
    static bool saveImage(const std::string & fileName, const PixelBuffer* bufferToSave);
private:
    //bool isValidImageFile(const std::string & fileName);
    static IMAGE_TYPE getImageType(const std::string & fileName);
};

#endif
