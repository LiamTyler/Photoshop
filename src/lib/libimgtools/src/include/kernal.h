/*******************************************************************************
 * Name            : kernal.h
 * Project         : FlashPhotoApp
 * Module          : Parent Kernal class
 * Description     : Header of Kernal
 * Copyright       : Group Bits Please
 * Creation Date   : 11/13/16
 * Original Author : Group Bits Please
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNAL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNAL_H_

#include <string>
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/color_data.h"

using image_tools::PixelBuffer;
using image_tools::ColorData;

/**
 * @brief Superclass for all kernals
 *
 * Kernals are two dimensional arrays that are used in convolution filters.
 * A kernal is centered over a pixel, and a weighted sum is performed between
 * all the pixels beneath the kernal after the pixel gets multiplied by the
 * amount in that element of the kernal.
 *
 */
class Kernal {
 public:
  Kernal(int width, int height);
  Kernal();
  virtual ~Kernal();
  Kernal(const Kernal& k);
  Kernal& operator=(const Kernal& k);
  /**
   * @brief Function that calculates what the next pixel should be after
   * applying the kernal to it.
   *
   * Centers the kernal over given pixel, multiplies each element according
   * to the value of the corresponding kernal element, and adds them up.
   *
   * @param[in] oldimage The image we are filtering
   * @param[in] start_x The x position of the pixel we are filtering
   * @param[in] start_y The y position of the pixel we are filtering
   *
   * @return The filtered pixel
   */
  ColorData ApplyKernal(PixelBuffer* oldimage, int start_x, int start_y);
  /**
   * @brief Resize the kernal to the given parameters
   */
  void Resize(int width, int height);
  inline int get_width() { return width_; }
  inline int get_height() { return height_; }
  inline float** get_kernal() { return kernal_; }
  /**
   * @brief Prints out the kernal values. Used for debugging purposes.
   */
  void print(std::ostream& out) const;

 protected:
  /**
   * @brief Dynamically allocate memory for the kernal
   */
  void AllocateKernal(int width, int height);
  void DeallocateKernal();
  /**
   * @brief Give each element in the kernal it's value
   *
   * This function is implemented by all the inherited kernal classes,
   * and each define the values in the kernal.
   */
  virtual void InitializeKernal() = 0;

 private:
  int width_;  /**< The kernal width */
  int height_;  /**< The kernal height */
  float** kernal_;  /** The 2D array that is the core of the kernal object  */
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNAL_H_
