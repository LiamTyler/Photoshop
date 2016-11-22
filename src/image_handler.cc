/*******************************************************************************
 * Name            : ImageHandler.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of ImageHandler class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 11/13/15
 * Original Author : Group Bits Please
 *
 ******************************************************************************/
#include "include/image_handler.h"

#include "include/pixel_buffer.h"
#include "include/color_data.h"

#include "include/ipng_handler.h"
#include "include/ijpg_handler.h"
#include "include/io_manager.h"

using image_tools::ColorData;
using image_tools::PixelBuffer;

// Decides whether the file is PNG or JPEG. Sends to appropriate handler.
// Returns new image if successful or error message if failed
PixelBuffer* ImageHandler::LoadImage(const std::string & file_name) {
    IMAGE_TYPE image_type = GetImageType(file_name);
    PixelBuffer* loaded_image = NULL;
    if (image_type == PNG_IMAGE) {
        loaded_image = IPNGHandler::LoadImage(file_name);
    } else if (image_type == JPG_IMAGE) {
        loaded_image = IJPGHandler::LoadImage(file_name);
    }  else {
        fprintf(stderr, "invalid entry\n");
    }
    return loaded_image;
}

// Decides whether the file is PNG or JPEG. Sends to appropriate handler.
bool ImageHandler::SaveImage(const std::string & file_name,
                             const PixelBuffer* buffer_to_save) {
    IMAGE_TYPE imageType = GetImageType(file_name);
    bool success = false;
    if (imageType == PNG_IMAGE) {
        success = IPNGHandler::SaveImage(file_name, buffer_to_save);
    } else if (imageType == JPG_IMAGE) {
        success = IJPGHandler::SaveImage(file_name, buffer_to_save);
    }  else {
        fprintf(stderr, "invalid entry\n");
    }
    return success;
}

// Decides file type via suffix
ImageHandler::IMAGE_TYPE
    ImageHandler::GetImageType(const std::string & file_name) {
    if (file_name.find(".png", file_name.size()-5) != std::string::npos) {
        return PNG_IMAGE;
    } else if (file_name.find(".jpg", file_name.size()-5)
                                        != std::string::npos ||
              file_name.find(".jpeg", file_name.size()-6)
                                        != std::string::npos) {
        return JPG_IMAGE;
    } else {
        return UNKNOWN_IMAGE;
    }
}
