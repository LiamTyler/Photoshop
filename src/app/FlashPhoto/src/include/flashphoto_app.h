/*******************************************************************************
 * Name            : flashphoto_app.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Header file for FlashPhotoApp class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_APP_FLASHPHOTO_SRC_INCLUDE_FLASHPHOTO_APP_H_
#define SRC_APP_FLASHPHOTO_SRC_INCLUDE_FLASHPHOTO_APP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include "lib/libimgtools/src/include/base_gfx_app.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "app/FlashPhoto/src/include/flashphoto_filter_manager.h"
#include "app/FlashPhoto/src/include/flashphoto_io_manager.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/state_manager.h"
#include "lib/libimgtools/src/include/tool.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class FlashPhotoApp : public BaseGfxApp {
 public:
  FlashPhotoApp(int width, int height);
  virtual ~FlashPhotoApp(void);

  void MouseDragged(int x, int y);
  void MouseMoved(int x, int y);
  void LeftMouseDown(int x, int y);
  void LeftMouseUp(int x, int y);
  void Display(void);
  void GluiControl(int control_id);
  void loadImageToCanvas(void);

  /**
   * @brief Initialize the FlashPhotoApp
   *
   * @param[in] argc Unused--required by BaseGfxApp
   * @param[in] argv Unused--required by BaseGfxApp
   * @param[in] x Unused--required by BaseGfxApp
   * @param[in] y Unused--required by BaseGfxApp
   * @param[in] background_color The initial canvas color
   */
  void Init(
      int argc,
      char *argv[],
      int x,
      int y,
      ColorData background_color);

 private:
  /**
   * @brief Update the colors displayed on the GLUI control panel after updating
   * their values in FlashPhoto
   *
   */
  void update_colors(void);

  /**
   * @brief Initialize the GLUI interface
   *
   */
  void InitGlui(void);

  /**
   * @brief Initialize OpenGL
   *
   */
  void InitGraphics(void);

  /**
   * @brief Initialize the buffers for the main window
   */
  void InitializeBuffers(ColorData initial_color,
                         int width, int height);

  /**
   * @brief Initialize functions to load/save images
   */
  // void LoadImageToCanvas(void);

  // void SaveCanvasToFile(void);

  void UpdateScratch(void);

  /* Copy/move assignment/construction disallowed */
  FlashPhotoApp(const FlashPhotoApp &rhs) = delete;
  FlashPhotoApp& operator=(const FlashPhotoApp &rhs) = delete;

  /**
   * @brief Manager for all filter operations
   */
  FlashPhotoFilterManager filter_manager_;

  /**
   * @brief Manager for all I/O operations
   */
  FlashPhotoIOManager io_manager_;

  /**
   * @brief Manager for redo/undo stack
   */
  StateManager state_manager_;

  /**
   * @brief A collection of GLUI spinners for RGB control elements.
   */
  struct {
    GLUI_Spinner *spinner_red;
    GLUI_Spinner *spinner_green;
    GLUI_Spinner *spinner_blue;
  } glui_ctrl_hooks_;

  /** Pointer to pixel data for the screen */
  PixelBuffer *display_buffer_;
  PixelBuffer *scratch_buffer_;

  // These are used to store the selections from the GLUI user interface
  int cur_tool_index_;  /**< Currently selected tool from UI */
  Tool* cur_tool_;
  std::vector<Tool*> tools_;

  int last_x_;
  int last_y_;

  float cur_color_red_;
  float cur_color_green_;
  float cur_color_blue_;

  ColorData current_color_;
};

}  /* namespace image_tools */

#endif  // SRC_APP_FLASHPHOTO_SRC_INCLUDE_FLASHPHOTO_APP_H_
