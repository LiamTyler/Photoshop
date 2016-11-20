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
#include "include/ImageHandler.h"

#include "include/pixel_buffer.h"
#include "include/color_data.h"

#include "include/IPNGHandler.h"
#include "include/IJPGHandler.h"

using image_tools::ColorData;
using image_tools::PixelBuffer;


PixelBuffer* ImageHandler::loadImage(const std::string & fileName) {
    IMAGE_TYPE imageType = getImageType(fileName);
    PixelBuffer* loadedImage = NULL;
    if (imageType == PNG_IMAGE) {
        loadedImage = IPNGHandler::loadImage(fileName);
    } else if (imageType == JPG_IMAGE) {
        loadedImage = IJPGHandler::loadImage(fileName);
    }  else {
        // how to error out?
    }
    return loadedImage;
}

bool ImageHandler::saveImage(const std::string & fileName,
                             const PixelBuffer* bufferToSave) {
    IMAGE_TYPE imageType = getImageType(fileName);
    bool success = false;
    if (imageType == PNG_IMAGE) {
        success = IPNGHandler::saveImage(fileName, bufferToSave);
    } else if (imageType == JPG_IMAGE) {
        success = IJPGHandler::saveImage(fileName, bufferToSave);
    }  else {
        // how to error out?
    }
    return success;
}

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
