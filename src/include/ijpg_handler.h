
#ifndef SRC_INCLUDE_IJPGHANDLER_
#define SRC_INCLUDE_IJPGHANDLER_

#include <stdio.h>
#include <string>

#include <jpeglib.h>
#include <setjmp.h>

#include "include/image_handler.h"
#include "include/pixel_buffer.h"

using image_tools::PixelBuffer;

class IJPGHandler : public ImageHandler {
public:
    static PixelBuffer* loadImage(const std::string fileName);
    static bool saveImage(const std::string fileName, const PixelBuffer* bufferToSave);
private:
    struct my_error_mgr {
        jpeg_error_mgr pub;	/* "public" fields */
        jmp_buf setjmp_buffer;	/* for return to caller */
    };
};

#endif // SRC_INCLUDE_IJPGHANDLER_
