/*******************************************************************************
 * Name            : BaseGfxApp.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Base class for  graphics applications built on top of
 *                   GLUI/GLUT toolkits
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_BASE_GFX_APP_H_
#define SRC_INCLUDE_BASE_GFX_APP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "GL/glui.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is a base class for graphics applications built on top of the
 * GLUT and GLUI toolkits.
 * GLUT and GLUI are C libraries, so one function of this class is to wrap the
 * funcationality they provide in a class structure that lends  itself to C++.
 * To receive callbaks from GLUT and GLUI that allow you to render graphics and
 * respond to user interface events, simply override the  virtual methods in
 * this class within your own subclass.
 */
class BaseGfxApp {
 public:
  BaseGfxApp(
      int width,
      int height);
  virtual ~BaseGfxApp(void);

  /**
   * @brief Initialize the the application.
   * This is separate from construction, which is only intended to put the
   * object in a valid state. If you override this, be sure to still call the
   * super class version.
   */
  virtual void Init(int argc,
                    char* argv[],
                    int x,
                    int y,
                    unsigned glut_flags,
                    bool create_glui_win,
                    int glui_win_x,
                    int glui_win_y);

  /**
   * @brief Set the window/icon title for the application
   */
  void set_caption(const std::string& caption);

  /**
   * @brief Set the dimensions of the application window.
   */
  void SetWindowDimensions(int width, int height);

  /*
   * @brief Start the program.
   * This function will not return until the graphics window is closed (unless
   * you segfault).
   */
  void RunMainLoop(void);

  /*
   * @brief Draw graphics on the screen.
   * Subclasses MUST provide this method.
   */
  virtual void Display(void) = 0;

  /**
   * @brief Draw an array of pixel data on the screen.
   */
  void DrawPixels(
      int start_x,
      int start_y,
      int width,
      int height,
      void const *const pixels);

  /**
   * @brief Redraw the screen.
   * @param[in] delta_time_ms Milliseconds since the last redraw of the screen
   */
  virtual void Update(int delta_time_ms) {}

  /**
   * @brief Callback for mouse moving interface event in the GLUT window
   * Note that (0,0) is in the lower right corner of the image, (this is what is
   * returned from GLUT), which is NOT the same as the coordinate system
   * definition for the PixelBuffer class. Your implementation will need to
   * account for this.
   */
  virtual void MouseMoved(int x, int y) {}

  /**
   * @brief Callback for mouse dragged interface event in the GLUT window
   */
  virtual void MouseDragged(int x, int y) {}

  /**
   * @brief Callback for left mouse click interface event in the GLUT window
   */
  virtual void LeftMouseDown(int x, int y) {}

  /**
   * @brief Callback for left mouse click release interface event in the GLUT
   * window
   */
  virtual void LeftMouseUp(int x, int y) {}

  /**
   * @brief Callback for right mouse click interface event in the GLUT window
   */
  virtual void RightMouseDown(int x, int y) {}

  /**
   * @brief Callback for right mouse click release interface event in the GLUT
   * window
   */
  virtual void RightMouseUp(int x, int y) {}

  /**
   * @brief Callback for middle mouse click interface event in the GLUT window
   */
  virtual void MiddleMouseDown(int x, int y) {}

  /**
   * @brief Callback for middle mouse click release interface event in the GLUT
   * window
   */
  virtual void MiddleMouseUp(int x, int y) {}

  /**
   * @brief Callback for keyboard key press interface event in the GLUT window
   */
  virtual void Keyboard(unsigned char c, int x, int y) {}

  /**
   * @brief Callback for keyboard special key press interface event in the GLUT
   * window
   */
  virtual void KeyboardSpecial(int key, int x, int y) {}

  /**
   * @brief Callback for keyboard key press release mouse moving interface event
   * in the GLUT window
   */
  virtual void KeyboardUp(unsigned char c, int x, int y) {}

  /**
   * @brief Callback for keyboard special key press release interface  event in
   * the GLUT window
   */
  virtual void KeyboardSpecialUp(int key, int x, int y) {}

  /**
   * @brief Callback that tells you when the user has interacted with a GLUI
   * widget
   */
  virtual void GluiControl(int control_id) {}

  /**
   * @brief resize the graphics window on the screen.
   * GLUT calls this when the user resizes the graphics window by dragging on it
   * with the mouse. The default implementation in BaseGfxApp is to ignore this
   * interaction and force the window to remain the same size. But, if desired,
   * subclasses can override this method and implement the logic to allow for
   * interactive resizing of windows.
   */
  virtual void Reshape(int width, int height);

  /**
   * @brief Clear the screen and call display().
   * Subclasses would only need to override this method if they need direct
   * control over clearing the the screen, which is usually not the case.
   */
  virtual void RenderOneFrame(void);

  /**
   * @brief Get the width of the application
   * @return The width
   */
  inline int width(void) const { return width_; }

  /**
   * @brief Get the height of the application
   * @return The height
   */
  inline int height(void) const { return height_; }

  /**
   * @brief Get the handle for the GLUI window
   * @return The handle
   */
  inline int handle(void) { return glut_window_handle_; }

  /**
   * @brief Get the handle for the GLUI
   * @return The GLUI handle
   */
  inline GLUI* glui(void) { return glui_; }

 protected:
  /**
   * GLUT and GLUI event callbacks are sent to the current
   * window/app. Right now, there is only one window anyway (not counting
   * the GLUI UI window.. in the future could be extended to support more
   * windows.  In any case, some structure like this is always needed when
   * using glut with C++, since the glut callbacks must be either global or
   * static functions.
   **/
  static void s_reshape(int width, int height);
  static void s_keyboard(unsigned char c, int x, int y);
  static void s_keyboardspecial(int key, int x, int y);
  static void s_keyboardup(unsigned char c, int x, int y);
  static void s_keyboardspecialup(int key, int x, int y);
  static void s_mousemotion(int x, int y);
  static void s_mousebtn(int b, int s, int x, int y);
  static void s_draw(void);
  static void s_gluicallback(int control_id);
  static void s_idle(void);

  /**
   * @brief Get the drag
   * @return The drag
   */
  inline bool drag(void) { return drag_; }

  /**
   * @brief Get the width
   * @return The width
   */
  inline int width(void) { return width_; }

  /**
   * @brief Get the height
   * @return The height
   */
  inline int height(void) { return height_; }

  /**
   * @brief Get a handle on the application
   * @return The application handle
   */
  inline BaseGfxApp* s_current_app(void) { return s_current_app_; }

 private:
  /* Copy assignment/construction is disallowed */
  BaseGfxApp(const BaseGfxApp &rhs) = delete;
  BaseGfxApp& operator=(const BaseGfxApp &rhs) = delete;

  int glut_window_handle_; /**< Underlying glut window handle */

  GLUI *glui_; /**< Pointer to GLUI master */

  bool drag_; /**< Indicates whether the mouse is currently pressed  */
  int width_;
  int height_;
  int milliseconds_; /**< ms since last update  */

  static BaseGfxApp *s_current_app_;

  /** Has glutInit been called? (only allowed once per program) */
  static bool s_glut_initialized_;
};

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_BASE_GFX_APP_H_ */
