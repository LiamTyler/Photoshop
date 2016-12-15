/*******************************************************************************
 * Name            : mia_io_manager.h
 * Project         : MIO
 * Module          : io_manager
 * Description     : Header for MIA IOManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_INCLUDE_MIA_IO_MANAGER_H_
#define SRC_APP_MIA_SRC_INCLUDE_MIA_IO_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/io_manager.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The manager for I/O operations in MIA. This includes
 * initializing GLUI control elements related to image loading/saving, as well
 * as handling the load/save operations themselves. The load operation includes
 * validating the image type and filesystem permissions before the load will
 * proceed. It also handles loading an image from a file to the stamp.
 */
class MIAIOManager : public IOManager {
 public:
  MIAIOManager();
  virtual ~MIAIOManager() {}

  /**
   * @brief Initialize GLUI control elements for IO management
   *
   * @param glui GLUI handle
   * @param s_gluicallback Callback to install
   * @return The initialized IO panel handle
   */
  GLUI_Panel* InitGlui(const GLUI *const glui,
                       void (*s_gluicallback)(int));

  std::string GetFile(void);

  /**
   * @brief Load the current image into the buffer
   *
   * @param[in] buff The buffer to load the image into
   *
   * @return The new image
   */
  PixelBuffer* LoadImageToCanvas(PixelBuffer* buff);

  /**
   * @brief Load the given image into the buffer
   *
   * @param[in] buff The buffer to load the image into
   * @param[in] fname The name of the image to load
   *
   * @return The new image
   */
  PixelBuffer* LoadSelectedImageToCanvas(PixelBuffer* buff,
          const std::string& fname);

  /**
   * @brief Load the next image into the canvas
   *
   * @param[in] buff The buffer to load the image into
   *
   * @return The next image
   */
  PixelBuffer* LoadNextImage(PixelBuffer* buff);

  /**
   * @brief Load the previous image into the canvas
   *
   * @param[in] buff The buffer to load the image into
   *
   * @return The previous image
   */
  PixelBuffer* LoadPreviousImage(PixelBuffer* buff);

  /**
   * @brief Set the next and previous text for the glui
   */
  void set_next_previous(void);
  void set_image_file(const std::string & fname_in);
  std::string image_name_plus_seq_offset(const std::string& filename,
                                         int offset);

 private:
  const int kDigitCount = 3;

  /* Copy/move assignment/construction disallowed */
  MIAIOManager(const MIAIOManager &rhs) = delete;
  MIAIOManager& operator=(const MIAIOManager &rhs) = delete;

  void prev_image_toggle(bool enabled) {
    UICtrl::button_toggle(prev_image_btn_, enabled);
  }
  void next_image_toggle(bool enabled) {
    UICtrl::button_toggle(next_image_btn_, enabled);
  }

  /* data members */
  GLUI_Button* next_image_btn_;
  GLUI_Button* prev_image_btn_;
  std::string prev_file_name_;
  std::string next_file_name_;
  std::string current_file_;
};

}  /* namespace image_tools */

#endif  /* SRC_APP_MIA_SRC_INCLUDE_MIA_IO_MANAGER_H_ */
