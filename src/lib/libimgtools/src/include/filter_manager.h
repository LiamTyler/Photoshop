/*******************************************************************************
 * Name            : filter_manager.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for FilterManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_MANAGER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "GL/glui.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Manager for all aspects of filters in FlashPhoto, including
 * initialization of GLUI control elements for filters, filter creation,
 * application, deletion.
 */
class FilterManager {
 public:
  FilterManager();
  virtual ~FilterManager() {}

  /**
   * @brief Apply a blur filter to the buffer, blurring sharply defined edges
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyBlur(PixelBuffer* oldimage, PixelBuffer* newimage);

  /**
   * @brief Apply a sharpening filter to the buffer, sharpening blurry/undefined
   * edges
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplySharpen(PixelBuffer* oldimage, PixelBuffer* newimage);

  /**
   * @brief Apply a motion blurring filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyMotionBlur(PixelBuffer* oldimage, PixelBuffer* newimage);

  /**
   * @brief Apply an edge detection filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyEdgeDetect(PixelBuffer* oldimage, PixelBuffer* newimage);

  /**
   * @brief Apply a threshold detection filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyThreshold(PixelBuffer* oldimage, PixelBuffer* newimage);

  /**
   * @brief Apply a channel filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyChannel(PixelBuffer* oldimage, PixelBuffer* newimage);

  /**
   * @brief Apply a channel filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplySaturate(PixelBuffer* oldimage, PixelBuffer* newimage);


  /**
   * @brief Apply a quantization filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyQuantize(PixelBuffer* oldimage, PixelBuffer* newimage);

  /**
   * @brief Apply a special filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplySpecial(PixelBuffer* oldimage, PixelBuffer* newimage);

  /**
   * @brief Initialize the elements of the GLUI interface required by the
   * FilterManager
   *
   * @param glui GLUI handle
   * @param s_gluicallback Callback to install
   */
  virtual GLUI_Panel* InitGlui(const GLUI *const glui,
                               void (*s_gluicallback)(int));

 protected:
  void AddBlurToGLUI(GLUI_Panel *filter_panel, void (*s_gluicallback)(int));
  void AddMotionBlurToGLUI(GLUI_Panel *filter_panel,
                           void (*s_gluicallback)(int));
  void AddSharpenToGLUI(GLUI_Panel *filter_panel,
                        void (*s_gluicallback)(int));
  void AddEdgeDetectToGLUI(GLUI_Panel *filter_panel,
                           void (*s_gluicallback)(int));
  void AddThresholdToGLUI(GLUI_Panel *filter_panel,
                          void (*s_gluicallback)(int));
  void AddSaturationToGLUI(GLUI_Panel *filter_panel,
                           void (*s_gluicallback)(int));
  void AddChannelToGLUI(GLUI_Panel *filter_panel,
                        void (*s_gluicallback)(int));
  void AddQuantizationToGLUI(GLUI_Panel *filter_panel,
                             void (*s_gluicallback)(int));
  void AddEmbossToGLUI(GLUI_Panel *filter_panel,
                             void (*s_gluicallback)(int));

 private:
  FilterManager(const FilterManager& rhs) = delete;
  FilterManager& operator=(const FilterManager& rhs) = delete;
  float channel_color_red_;
  float channel_color_green_;
  float channel_color_blue_;
  float saturation_amount_;
  float threshold_amount_;
  float blur_amount_;
  float sharpen_amount_;
  float motion_blur_amount_;
  enum UICtrl::MotionBlurDirection motion_blur_direction_;
  int quantize_bins_;
};

}  /* namespace image_tools */

#endif  /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_MANAGER_H_ */
