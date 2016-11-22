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
PixelBuffer* ImageHandler::loadImage(const std::string & fileName) {
    IMAGE_TYPE imageType = getImageType(fileName);
    PixelBuffer* loadedImage = NULL;
    if (imageType == PNG_IMAGE) {
        loadedImage = IPNGHandler::loadImage(fileName);
    } else if (imageType == JPG_IMAGE) {
        loadedImage = IJPGHandler::loadImage(fileName);
    }  else {
        fprintf(stderr, "invalid entry\n");
    }
    return loadedImage;
}

// Decides whether the file is PNG or JPEG. Sends to appropriate handler.
bool ImageHandler::saveImage(const std::string & fileName,
                             const PixelBuffer* bufferToSave) {
    IMAGE_TYPE imageType = getImageType(fileName);
    bool success = false;
    if (imageType == PNG_IMAGE) {
        success = IPNGHandler::saveImage(fileName, bufferToSave);
    } else if (imageType == JPG_IMAGE) {
        success = IJPGHandler::saveImage(fileName, bufferToSave);
    }  else {
        fprintf(stderr, "invalid entry\n");
    }
    return success;
}

// Decides file type via suffix
ImageHandler::IMAGE_TYPE
                      ImageHandler::getImageType(const std::string & fileName) {
    if (fileName.find(".png", fileName.size()-5) != std::string::npos) {
        return PNG_IMAGE;
    } else if (fileName.find(".jpg", fileName.size()-5) != std::string::npos ||
              fileName.find(".jpeg", fileName.size()-6) != std::string::npos) {
        return JPG_IMAGE;
    } else {
        return UNKNOWN_IMAGE;
    }
}
