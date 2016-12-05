/*******************************************************************************
 * Name            : io_manager.cc
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Implementation of MIAIOManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/MIA/src/include/mia_io_manager.h"

#include <assert.h>
#include <iostream>
#include <sstream>

/* FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIAIOManager::MIAIOManager(void) :
    IOManager(),
    next_image_btn_(nullptr),
    prev_image_btn_(nullptr),
    prev_file_name_(),
    next_file_name_() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
GLUI_Panel* MIAIOManager::InitGlui(const GLUI *const glui,
                         void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *image_panel = new GLUI_Panel(const_cast<GLUI*>(glui),
                                           "Image I/O");
  AddFileBrowserToGLUI(image_panel, s_gluicallback);
  AddSaveCanvasToGLUI(image_panel, s_gluicallback);
  new GLUI_Separator(image_panel);

  prev_image_btn_  = new GLUI_Button(image_panel, "Previous Image",
                                     UICtrl::UI_PREV_IMAGE_BUTTON,
                                     s_gluicallback);
  next_image_btn_ = new GLUI_Button(image_panel, "Next Image",
                                    UICtrl::UI_NEXT_IMAGE_BUTTON,
                                    s_gluicallback);

  next_image_toggle(false);
  prev_image_toggle(false);
  return image_panel;
}

void MIAIOManager::LoadNextImage(void) {
  set_image_file(next_file_name_);
  LoadImageToCanvas();
}

void MIAIOManager::LoadPreviousImage(void) {
  set_image_file(prev_file_name_);
  LoadImageToCanvas();
}

void MIAIOManager::LoadImageToCanvas(void) {
  // Determining whether there are next or previous images
  next_file_name_ = image_name_plus_seq_offset(file_name(), 1);
  prev_file_name_ = image_name_plus_seq_offset(file_name(), -1);

  next_image_toggle(is_valid_image_file(next_file_name_));
  prev_image_toggle(is_valid_image_file(prev_file_name_));
}

void MIAIOManager::set_image_file(const std::string & fname_in) {
  // If a directory was selected instead of a file, use the
  // latest file typed or selected.
  std::string image_file = fname_in;
  if (!is_valid_image_file_name(image_file)) {
    image_file = file_name();
  }

  // TOGGLE SAVE FEATURE
  // If no file is selected or typed, don't allow file to be saved. If
  // there is a file name, then allow file to be saved to that name.

  if (!is_valid_image_file_name(image_file)) {
    save_file_label()->set_text("Will save image: none");
    save_canvas_toggle(false);
  } else {
    save_file_label()->set_text((std::string("Will save image: ") +
                                 image_file).c_str());
    save_canvas_toggle(true);
  }

  // TOGGLE LOAD FEATURE

  // If the file specified cannot be opened, then disable stamp and canvas
  // loading.
  if (is_valid_image_file(image_file)) {
    load_canvas_toggle(true);

    current_file_label()->set_text((std::string("Will load: ") +
                                    image_file).c_str());
    file_name_box()->set_text(image_file);
  } else {
    load_canvas_toggle(false);
    current_file_label()->set_text("Will load: none");
  }
}

std::string MIAIOManager::image_name_plus_seq_offset(
    const std::string& filename,
    int offset) {

  std::string extension, name, number;
  size_t dot_pos = file_name().find_last_of(".");
  if (dot_pos ==  std::string::npos || dot_pos == 0) {
    return "";
  }

  extension = filename.substr(dot_pos+1);
  name = filename.substr(0, dot_pos);
  if (static_cast<int>(name.length()) < kDigitCount) {
    return "";
  }

  number = name.substr(name.length()-kDigitCount);
  name = name.substr(0, name.length()-kDigitCount);
  int num;
  std::istringstream(number) >> num;
  int output_num = num +offset;
  if (output_num < 0) {
    return "";
  }
  std::stringstream ss;
  ss << output_num;
  std::string output_number;
  ss >> output_number;

  // Append zero chars
  int str_length = output_number.length();
  for (int i = 0; i < kDigitCount - str_length; i++) {
    output_number = "0" + output_number;
  }

  return (name + output_number + "." + extension);
}

}  /* namespace image_tools */
