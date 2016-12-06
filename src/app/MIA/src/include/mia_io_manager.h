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
/* FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */
#include "app/MIA/src/include/io_manager.h"

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
  ~MIAIOManager() {}

  /**
   * @brief Initialize GLUI control elements for IO management
   *
   * @param glui GLUI handle
   * @param s_gluicallback Callback to install
   * @return The initialized IO panel handle
   */
  GLUI_Panel* InitGlui(const GLUI *const glui,
                       void (*s_gluicallback)(int));

  void LoadImageToCanvas(void);
  void LoadNextImage(void);
  void LoadPreviousImage(void);
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
};

}  /* namespace image_tools */

#endif  /* SRC_APP_MIA_SRC_INCLUDE_MIA_IO_MANAGER_H_ */
