/*******************************************************************************
 * Name            : imagehandler.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Header of ImageHandler
 * Copyright       : Group Bits Please
 * Creation Date   : 11/21/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IMAGE_HANDLER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IMAGE_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

/**
 * @brief Class that handles overall loading and saving of images
 *
 * This class will figure out the type of the image, and if the type is jpg or
 * png, it will call the appropriate functions to handle that file type for
 * both loading and saving.
 *
 */
class ImageHandler {
 public:
  /**
   * @brief Enum used to enumerate the valid image types for this app
   */
  enum IMAGE_TYPE {
    PNG_IMAGE,
    JPG_IMAGE,
    UNKNOWN_IMAGE
  };

  /**
   * @brief Returns a PixelBuffer with the requested image to load
   */
  static PixelBuffer* LoadImage(const std::string & file_name);

  /**
   * @brief Saves the Buffer passed in to the specified file_name 
   */
  static bool SaveImage(const std::string & file_name,
                        const PixelBuffer* bufferToSave);
  /**
   * @brief Determines the image type of the file passed in
   *
   * @return ImageHandler::IMAGE_TYPE (the enumerated image type)
   */
  static IMAGE_TYPE GetImageType(const std::string & file_name);
};

#endif  /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IMAGE_HANDLER_H_ */
