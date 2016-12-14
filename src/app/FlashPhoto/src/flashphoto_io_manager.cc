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
#include "app/FlashPhoto/src/include/flashphoto_io_manager.h"
#include <assert.h>
#include <iostream>
#include <sstream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
GLUI_Panel* FlashPhotoIOManager::InitGlui(const GLUI *const glui,
        void (*s_gluicallback)(int)) {
    new GLUI_Column(const_cast<GLUI*>(glui), true);
    GLUI_Panel *image_panel = new GLUI_Panel(const_cast<GLUI*>(glui),
            "Image I/O");
    AddFileBrowserToGLUI(image_panel, s_gluicallback);
    AddLoadStampToGLUI(image_panel, s_gluicallback);

    new GLUI_Separator(image_panel);
    AddSaveCanvasToGLUI(image_panel, s_gluicallback);
    new GLUI_Separator(image_panel);

    /*
       new GLUI_Column(const_cast<GLUI*>(glui), true);
       GLUI_Panel *image_panel = new GLUI_Panel(const_cast<GLUI*>(glui),
       "Image I/O");
       file_browser_ = new GLUI_FileBrowser(image_panel,
       "Choose Image",
       false,
       UICtrl::UI_FILE_BROWSER,
       s_gluicallback);

       file_browser_->set_h(400);

       file_name_box_ = new GLUI_EditText(image_panel ,
       "Image:",
       file_name_,
       UICtrl::UI_FILE_NAME,
       s_gluicallback);
       file_name_box_->set_w(200);

       new GLUI_Separator(image_panel);

       current_file_label_ = new GLUI_StaticText(image_panel,
       "Will load image: none");
       load_canvas_btn_ = new GLUI_Button(image_panel,
       "Load Canvas",
       UICtrl::UI_LOAD_CANVAS_BUTTON,
       s_gluicallback);
       load_stamp_btn_ = new GLUI_Button(image_panel,
       "Load Stamp",
       UICtrl::UI_LOAD_STAMP_BUTTON,
       s_gluicallback);

       new GLUI_Separator(image_panel);

       save_file_label_ = new GLUI_StaticText(image_panel,
       "Will save image: none");

       save_canvas_btn_ = new GLUI_Button(image_panel,
       "Save Canvas",
       UICtrl::UI_SAVE_CANVAS_BUTTON,
       s_gluicallback);

       load_canvas_toggle(false);
       load_stamp_toggle(false);
       save_canvas_toggle(false);
       */

    return image_panel;
}

}  /* namespace image_tools */
