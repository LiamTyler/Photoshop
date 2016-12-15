/*******************************************************************************
 * Name            : mia_app.cc
 * Project         : MIA
 * Module          : App
 * Description     : Implementation of MIA
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 5/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/MIA/src/include/mia_app.h"
#include <string>
#include <iostream>

/* FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIAApp::MIAApp(int w, int h,
               const std::string& markerFname) : BaseGfxApp(w, h),
                                                  filter_manager_(),
                                                  io_manager_(),
                                                  state_manager_(),
                                                  display_buffer_(nullptr),
                                                  scratch_buffer_(nullptr),
                                                  marker_fname_(markerFname),
                                                  cur_tool_(0) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MIAApp::Init(
    int argc,
    char* argv[],
    int x,
    int y,
    ColorData background_color) {
  BaseGfxApp::Init(argc, argv,
                   x, y,
                   GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH,
                   true,
                   width()+51,
                   50);

  // Set the name of the window
  set_caption("MIA");

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());

  InitGlui();
  InitGraphics();
}

void MIAApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

MIAApp::~MIAApp(void) {
  if (display_buffer_) {
    delete display_buffer_;
  }
  if (scratch_buffer_) {
    delete scratch_buffer_;
  }
}

void MIAApp::LeftMouseDown(int x, int y) {
  std::cout << "mousePressed " << x << " " << y << std::endl;
  // cur_tool_->ApplyTool(display_buffer_, current_color_,
  //                      x, y, last_x_, last_y_);
  // last_x_ = x;
  // last_x_ = y;
}

void MIAApp::LeftMouseUp(int x, int y) {
  std::cout << "mouseReleased " << x << " " << y << std::endl;
  // last_x_ = -1;
  // last_y_ = -1;
  state_manager_.Save(display_buffer_);
}

void MIAApp::InitializeBuffers(ColorData background_color,
                               int w, int h) {
  display_buffer_ = new PixelBuffer(w, h, background_color);
  scratch_buffer_ = new PixelBuffer(w, h, background_color);
}

void MIAApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  new GLUI_Column(glui(), false);
  GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
  {
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel, &cur_tool_,
                                                 UICtrl::UI_TOOLTYPE,
                                                 s_gluicallback);
    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Marker");
  }

  /* Initialize state management (undo, redo, quit) */
  state_manager_.InitGlui(glui(), s_gluicallback, display_buffer_);

  new GLUI_Button(const_cast<GLUI*>(glui()),
                  "Quit", UICtrl::UI_QUIT,
                  static_cast<GLUI_Update_CB>(exit));

  /* Initialize Filtering */
  filter_manager_.InitGlui(glui(), s_gluicallback);

  /* Initialize image I/O */
  io_manager_.InitGlui(glui(), s_gluicallback);
  return;
}

void MIAApp::Update(void) {
    PixelBuffer* d = display_buffer_;
    if (d->width() != scratch_buffer_->width() ||
        d->height() != scratch_buffer_->height()) {
        delete scratch_buffer_;
        scratch_buffer_ = new PixelBuffer(d->width(), d->height(),
                                          d->background_color());
    }
    BaseGfxApp::SetWindowDimensions(display_buffer_->width(),
                                  display_buffer_->height());
}

void MIAApp::GluiControl(int control_id) {
  switch (control_id) {
    case UICtrl::UI_APPLY_SHARP:
      filter_manager_.ApplySharpen(display_buffer_, scratch_buffer_);
      break;
    case UICtrl::UI_APPLY_EDGE:
      filter_manager_.ApplyEdgeDetect(display_buffer_, scratch_buffer_);
      break;
    case UICtrl::UI_APPLY_THRESHOLD:
      filter_manager_.ApplyThreshold(display_buffer_, scratch_buffer_);
      break;
    case UICtrl::UI_APPLY_SATURATE:
      filter_manager_.ApplySaturate(display_buffer_, scratch_buffer_);
      break;
    case UICtrl::UI_APPLY_CHANNEL:
      filter_manager_.ApplyChannel(display_buffer_, scratch_buffer_);
      break;
    case UICtrl::UI_APPLY_QUANTIZE:
      filter_manager_.ApplyQuantize(display_buffer_, scratch_buffer_);
      break;
    case UICtrl::UI_APPLY_BLUR:
      filter_manager_.ApplyBlur(display_buffer_, scratch_buffer_);
      break;
    case UICtrl::UI_FILE_BROWSER:
      io_manager_.set_image_file(io_manager_.file_browser()->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      display_buffer_ = io_manager_.LoadImageToCanvas(display_buffer_);
      Update();
      state_manager_.Save(display_buffer_);
      break;
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      // Reload the current directory:
      io_manager_.SaveCanvasToFile(display_buffer_);
      io_manager_.file_browser()->fbreaddir(".");
      break;
    case UICtrl::UI_NEXT_IMAGE_BUTTON:
      display_buffer_ = io_manager_.LoadNextImage(display_buffer_);
      Update();
      break;
    case UICtrl::UI_PREV_IMAGE_BUTTON:
      display_buffer_ = io_manager_.LoadPreviousImage(display_buffer_);
      Update();
      break;
    case UICtrl::UI_FILE_NAME:
      io_manager_.set_image_file(io_manager_.file_name());
      break;
    case UICtrl::UI_UNDO:
      display_buffer_ = state_manager_.UndoOperation(display_buffer_);
      Update();
      break;
    case UICtrl::UI_REDO:
      display_buffer_ = state_manager_.RedoOperation(display_buffer_);
      Update();
      break;
    default:
      break;
  }

  PixelBuffer* tmp;
  if (control_id >= UICtrl::UI_APPLY_BLUR &&
          control_id <= UICtrl::UI_APPLY_QUANTIZE) {
      tmp = display_buffer_;
      display_buffer_ = scratch_buffer_;
      scratch_buffer_ = tmp;
      state_manager_.Save(display_buffer_);
  }

  // Forces canvas to update changes made in this function
  glui()->post_update_main_gfx();
}
void MIAApp::InitGraphics(void) {
  // Initialize OpenGL for 2D graphics as used in the BrushWork app
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(0, width(), 0, height());
  glViewport(0, 0, width(), height());
}


}  /* namespace image_tools */
