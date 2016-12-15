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
#include <assert.h>
#include <cmath>
#include <string>
#include <iostream>
#include "lib/libimgtools/src/include/stamp_tool.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/image_handler.h"
#include "lib/libimgtools/src/include/tool_factory.h"

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
                                                  cur_tool_index_(0),
                                                  cur_tool_(nullptr),
                                                  tools_(),
                                                  last_x_(-1),
                                                  last_y_(-1),
                                                  current_color_(1, 0, 0) {}

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

  // Set up Tools
  std::cout << ToolFactory::TOOL_PEN << std::endl;
  Tool* t = ToolFactory::CreateTool(ToolFactory::TOOL_PEN);
  assert(t);
  tools_.push_back(t);
  t = ToolFactory::CreateTool(ToolFactory::TOOL_STAMP);
  assert(t);
  tools_.push_back(t);
  dynamic_cast<TStamp*>(tools_[1])->LoadImage(
    ImageHandler::LoadImage(marker_fname_));
  cur_tool_ = tools_[0];

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

void MIAApp::MouseDragged(int x, int y) {
    if (last_x_ != -1) {
    /* Find the distance between (last_x_, last_y_) and (x, y) and divide by
     * an eigth of the width of the mask to determine the number n times to
     * ApplyTool between (last_x_, last_y_) and (x, y) */
        int n = sqrt(pow((last_x_ - x), 2) +
                pow((last_y_ - y), 2))/(cur_tool_ -> get_width() / 8.0);
        float percent_step = 1.0/static_cast<float>(n);
        int base_x = last_x_;
        int base_y = last_y_;
        float dx = x - base_x;
        float dy = y - base_y;
        for (float i = percent_step; i < 1.0; i+=percent_step) {
            int new_x = base_x + (i * dx);
            int new_y = base_y + (i * dy);
            cur_tool_->ApplyTool(display_buffer_, current_color_, new_x, new_y,
                                 last_x_, last_y_);
            last_x_ = new_x;
            last_y_ = new_y;
        }
    }
    cur_tool_->ApplyTool(display_buffer_, current_color_, x, y,
            last_x_, last_y_);
    last_x_ = x;
    last_y_ = y;
}

void MIAApp::LeftMouseDown(int x, int y) {
    std::cout << "mousePressed " << x << " " << y << std::endl;
    cur_tool_->ApplyTool(display_buffer_, current_color_,
                         x, y, last_x_, last_y_);
    last_x_ = x;
    last_y_ = y;
}

void MIAApp::LeftMouseUp(int x, int y) {
    std::cout << "mouseReleased " << x << " " << y << std::endl;
    last_x_ = -1;
    last_y_ = -1;
    state_manager_.Save(display_buffer_);
}

void MIAApp::InitializeBuffers(ColorData background_color,
                               int w, int h) {
  display_buffer_ = new PixelBuffer(w, h, background_color);
  scratch_buffer_ = new PixelBuffer(w, h, background_color);
}

void MIAApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_index_ = 0;

  new GLUI_Column(glui(), false);
  GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
  {
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel, &cur_tool_index_,
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
    case UICtrl::UI_TOOLTYPE:
        cur_tool_ = tools_[cur_tool_index_];
        break;
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
