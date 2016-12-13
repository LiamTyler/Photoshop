/*******************************************************************************
 * Name            : imgtools_interface.h
 * Project         : FlashPhoto
 * Module          : imgtools_interface.h
 * Description     : Functions for things the libimgtools library
 * Copyright       : Group Bits Please 
 * Creation Date   : 12/6/16
 * Original Author : Liam Tyler
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IMGTOOLS_INTERFACE_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IMGTOOLS_INTERFACE_H_

#include <string>
#include "lib/libimgtools/src/include/pixel_buffer.h"



/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace imgtools {

/**
 * @brief Function that will apply the channel filter to oldimage
 * @param[in] oldimage The image to filter
 * @param[out] newimage The post-filtered image
 * @param[in] red The amount to scale the R value of the pixels
 * @param[in] green The amount to scale the G value of the pixels
 * @param[in] blue The amount to scale the B value of the pixels
 */
void ApplyChannel(PixelBuffer* oldimage, PixelBuffer* newimage,
                  float red, float green, float blue);

/**
 * @brief Function that will apply the saturate filter to oldimage
 * @param[in] oldimage The image to filter
 * @param[out] newimage The post-filtered image
 * @param[in] amt The amount to saturate by
 */
void ApplySaturate(PixelBuffer* oldimage, PixelBuffer* newimage, float amt);

/**
 * @brief Function that will apply the blur filter to oldimage
 * @param[in] oldimage The image to filter
 * @param[out] newimage The post-filtered image
 * @param[in] amt The amount to blur by
 */
void ApplyBlur(PixelBuffer* oldimage, PixelBuffer* newimage, float amt);

/**
 * @brief Function that will apply the sharpen filter to oldimage
 * @param[in] oldimage The image to filter
 * @param[out] newimage The post-filtered image
 * @param[in] amt The amount to sharpen by
 */
void ApplySharpen(PixelBuffer* oldimage, PixelBuffer* newimage, float amt);

/**
 * @brief Function that will apply the motion blur filter to oldimage
 * @param[in] oldimage The image to filter
 * @param[out] newimage The post-filtered image
 * @param[in] amt The amount to blur by
 * @param[in] direction The direction to blur in (ui_ctrl enum)
 */
void ApplyMotionBlur(PixelBuffer* oldimage, PixelBuffer* newimage,
                     int amt, int direction);

/**
 * @brief Function that will apply the edge detect filter to oldimage
 * @param[in] oldimage The image to filter
 * @param[out] newimage The post-filtered image
 */
void ApplyEdgeDetect(PixelBuffer* oldimage, PixelBuffer* newimage);

/**
 * @brief Function that will apply the quantize filter to oldimage
 * @param[in] oldimage The image to filter
 * @param[out] newimage The post-filtered image
 * @param[in] bins The number of bins to round the pixels into
 */
void ApplyQuantize(PixelBuffer* oldimage, PixelBuffer* newimage, int bins);

/**
 * @brief Function that will apply the threshold filter to oldimage
 * @param[in] oldimage The image to filter
 * @param[out] newimage The post-filtered image
 * @param[in] level The threshold for round pixels to 1 or 0
 */
void ApplyThreshold(PixelBuffer* oldimage, PixelBuffer* newimage, float level);

/**
 * @brief Function that will apply the emboss filter to oldimage
 * @param[in] oldimage The image to filter
 * @param[out] newimage The post-filtered image
 */
void ApplySpecial(PixelBuffer* oldimage, PixelBuffer* newimage);

/**
 * @brief Loads the specified image and return it
 * @param[in] file_name The name of the image to load (jpg or png)
 */
image_tools::PixelBuffer* LoadImage(const std::string& file_name);

/**
 * @brief Saves the specified image to the given file name
 * @param[in] file_name The name of the file to save
 * @param[in] bufferToSave The image to save
 *
 * @return Whether the image was saved successfully or not
 */
bool SaveImage(const std::string& file_name,
               const image_tools::PixelBuffer* bufferToSave);

/**
 * @brief Compares the two specified images to see if they are equal or not
 * @param[in] img1 The first image
 * @param[in] img2 The second image
 *
 * @return 1 if the images are equal, 0 if they are not
 */
int CompareImages(const PixelBuffer* img1, const PixelBuffer* img2);

}  /* namespace imgtools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IMGTOOLS_INTERFACE_H_
