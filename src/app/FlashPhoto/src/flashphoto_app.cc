/*******************************************************************************
 * Name            : flashphoto_app.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of FlashPhoto
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 * New Authors     : Liam Tyler
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/FlashPhoto/src/include/flashphoto_app.h"
#include <assert.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/tool_factory.h"
#include "lib/libimgtools/src/include/image_handler.h"
#include "lib/libimgtools/src/include/io_manager.h"
#include "lib/libimgtools/src/include/stamp_tool.h"

using std::cout;
using std::endl;
using image_tools::IOManager;

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FlashPhotoApp::FlashPhotoApp(int w, int h) : BaseGfxApp(w, h),
    filter_manager_(),
    io_manager_(),
    state_manager_(),
    glui_ctrl_hooks_(),
    display_buffer_(nullptr),
    scratch_buffer_(nullptr),
    cur_tool_index_(0),
    cur_tool_(nullptr),
    tools_(),
    last_x_(-1),
    last_y_(-1),
    cur_color_red_(0.0),
    cur_color_green_(0.0),
    cur_color_blue_(0.0),
    current_color_(ColorData(0, 0, 0)) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void FlashPhotoApp::Init(
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
    set_caption("FlashPhoto");

    // Set up Tools
    for (int i = 0; i < ToolFactory::num_tools(); i++) {
        Tool* t = ToolFactory::CreateTool(i);
        assert(t);
        tools_.push_back(t);
        // std::cout << "tool " << i << " created" << std::endl;
    }
    cur_tool_index_ = 0;
    cur_tool_ = tools_[0];
    last_x_ = -1;
    last_y_ = -1;

    // Initialize Interface
    InitializeBuffers(background_color, width(), height());

    InitGlui();
    InitGraphics();
}

void FlashPhotoApp::Display(void) {
    DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

FlashPhotoApp::~FlashPhotoApp(void) {
    if (display_buffer_) {
        delete display_buffer_;
    }
    if (scratch_buffer_) {
        delete scratch_buffer_;
    }
}

void FlashPhotoApp::UpdateScratch() {
    PixelBuffer* d = display_buffer_;
    if (d->width() != scratch_buffer_->width() ||
        d->height() != scratch_buffer_->height()) {
        delete scratch_buffer_;
        scratch_buffer_ = new PixelBuffer(d->width(), d->height(),
                                          d->background_color());
    }
}

void FlashPhotoApp::MouseDragged(int x, int y) {
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

void FlashPhotoApp::MouseMoved(int x, int y) {}

void FlashPhotoApp::LeftMouseDown(int x, int y) {
    std::cout << "mousePressed " << x << " " << y << std::endl;
    cur_tool_->ApplyTool(display_buffer_, current_color_,
                         x, y, last_x_, last_y_);
    last_x_ = x;
    last_y_ = y;
}

void FlashPhotoApp::LeftMouseUp(int x, int y) {
    std::cout << "mouseReleased " << x << " " << y << std::endl;
    last_x_ = -1;
    last_y_ = -1;
    state_manager_.Save(display_buffer_);
}

void FlashPhotoApp::InitializeBuffers(ColorData background_color,
        int w, int h) {
    display_buffer_ = new PixelBuffer(w, h, background_color);
    scratch_buffer_ = new PixelBuffer(w, h, background_color);
}

/*
// Copies the image that will load into the current buffer
// Also updates the window dimensions to fi the image
void FlashPhotoApp::LoadImageToCanvas(void) {
    delete display_buffer_;
    display_buffer_ = ImageHandler::LoadImage(
            io_manager_.file_browser()->get_file());
    UpdateScratch();
    // std::cout << "DB w: " << display_buffer_->width() << ", DB h: " << DB
    BaseGfxApp::SetWindowDimensions(display_buffer_->width(),
                                  display_buffer_->height());
}

// Function that calls saveImage from ImageHandler
void FlashPhotoApp::SaveCanvasToFile(void) {
     ImageHandler::SaveImage(io_manager_.file_browser()->get_file(),
                             display_buffer_);
}
*/

void FlashPhotoApp::InitGlui(void) {
    // Select first tool (this activates the first radio button in glui)
    cur_tool_index_ = 0;

    GLUI_Panel *toolPanel = new GLUI_Panel(glui(), "Tool Type");
    {
        GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel,
                                                     &cur_tool_index_,
                                                     UICtrl::UI_TOOLTYPE,
                                                     s_gluicallback);
        // Create interface buttons for different tools:
        for (int i = 0; i < ToolFactory::num_tools(); i++)
            new GLUI_RadioButton(radio, tools_[i]->name().c_str());
    }

    GLUI_Panel *color_panel = new GLUI_Panel(glui(), "Tool Color");
    {
        cur_color_red_ = 0;
        glui_ctrl_hooks_.spinner_red  = new GLUI_Spinner(color_panel, "Red:",
                &cur_color_red_,
                UICtrl::UI_COLOR_R,
                s_gluicallback);
        glui_ctrl_hooks_.spinner_red->set_float_limits(0, 1.0);

        cur_color_green_ = 0;
        glui_ctrl_hooks_.spinner_green = new GLUI_Spinner(color_panel, "Green:",
                &cur_color_green_,
                UICtrl::UI_COLOR_G,
                s_gluicallback);
        glui_ctrl_hooks_.spinner_green->set_float_limits(0, 1.0);

        cur_color_blue_ = 0;
        glui_ctrl_hooks_.spinner_blue  = new GLUI_Spinner(color_panel, "Blue:",
                &cur_color_blue_,
                UICtrl::UI_COLOR_B,
                s_gluicallback);
        glui_ctrl_hooks_.spinner_blue->set_float_limits(0, 1.0);

        new GLUI_Button(color_panel, "Red", UICtrl::UI_PRESET_RED,
                s_gluicallback);
        new GLUI_Button(color_panel, "Orange", UICtrl::UI_PRESET_ORANGE,
                s_gluicallback);
        new GLUI_Button(color_panel, "Yellow", UICtrl::UI_PRESET_YELLOW,
                s_gluicallback);
        new GLUI_Button(color_panel, "Green", UICtrl::UI_PRESET_GREEN,
                s_gluicallback);
        new GLUI_Button(color_panel, "Blue", UICtrl::UI_PRESET_BLUE,
                s_gluicallback);
        new GLUI_Button(color_panel, "Purple", UICtrl::UI_PRESET_PURPLE,
                s_gluicallback);
        new GLUI_Button(color_panel, "White", UICtrl::UI_PRESET_WHITE,
                s_gluicallback);
        new GLUI_Button(color_panel, "Black", UICtrl::UI_PRESET_BLACK,
                s_gluicallback);
    }
    update_colors();

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

void FlashPhotoApp::GluiControl(int control_id) {
    PixelBuffer* tmp;
    // std::cout << "db w: " << display_buffer_->width() << ", db h: " <<
    //    display_buffer_->height() << ", sb w: " << scratch_buffer_->width()
    //    << ", sb h: " << scratch_buffer_->height() << std::endl;
    switch (control_id) {
        case UICtrl::UI_TOOLTYPE:
            cur_tool_ = tools_[cur_tool_index_];
            break;
        case UICtrl::UI_PRESET_RED:
            cur_color_red_ = 1;
            cur_color_green_ = 0;
            cur_color_blue_ = 0;
            break;
        case UICtrl::UI_PRESET_ORANGE:
            cur_color_red_ = 1;
            cur_color_green_ = 0.5;
            cur_color_blue_ = 0;
            break;
        case UICtrl::UI_PRESET_YELLOW:
            cur_color_red_ = 1;
            cur_color_green_ = 1;
            cur_color_blue_ = 0;
            break;
        case UICtrl::UI_PRESET_GREEN:
            cur_color_red_ = 0;
            cur_color_green_ = 1;
            cur_color_blue_ = 0;
            break;
        case UICtrl::UI_PRESET_BLUE:
            cur_color_red_ = 0;
            cur_color_green_ = 0;
            cur_color_blue_ = 1;
            break;
        case UICtrl::UI_PRESET_PURPLE:
            cur_color_red_ = 0.5;
            cur_color_green_ = 0;
            cur_color_blue_ = 1;
            break;
        case UICtrl::UI_PRESET_WHITE:
            cur_color_red_ = 1;
            cur_color_green_ = 1;
            cur_color_blue_ = 1;
            break;
        case UICtrl::UI_PRESET_BLACK:
            cur_color_red_ = 0;
            cur_color_green_ = 0;
            cur_color_blue_ = 0;
            break;
        case UICtrl::UI_APPLY_BLUR:
            filter_manager_.ApplyBlur(display_buffer_, scratch_buffer_);
            break;
        case UICtrl::UI_APPLY_SHARP:
            filter_manager_.ApplySharpen(display_buffer_, scratch_buffer_);
            break;
        case UICtrl::UI_APPLY_MOTION_BLUR:
            filter_manager_.ApplyMotionBlur(display_buffer_, scratch_buffer_);
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
        case UICtrl::UI_APPLY_SPECIAL_FILTER:
            filter_manager_.ApplySpecial(display_buffer_, scratch_buffer_);
            break;
        case UICtrl::UI_FILE_BROWSER:
            io_manager_.set_image_file(io_manager_.file_browser()->get_file());
            break;
        case UICtrl::UI_LOAD_CANVAS_BUTTON:
            display_buffer_ = io_manager_.LoadImageToCanvas(display_buffer_);
            UpdateScratch();
            BaseGfxApp::SetWindowDimensions(display_buffer_->width(),
                                  display_buffer_->height());
            state_manager_.Save(display_buffer_);
            break;
        case UICtrl::UI_LOAD_STAMP_BUTTON:
            io_manager_.LoadImageToStamp(dynamic_cast<TStamp*>(
                        tools_[ToolFactory::TOOLS::TOOL_STAMP]));
            break;
        case UICtrl::UI_SAVE_CANVAS_BUTTON:
            io_manager_.SaveCanvasToFile(display_buffer_);
            // Reload the current directory:
            // SaveCanvasToFile();
            io_manager_.file_browser()->fbreaddir(".");
            break;
        case UICtrl::UI_FILE_NAME:
            io_manager_.set_image_file(io_manager_.file_name());
            break;
        case UICtrl::UI_UNDO:
            display_buffer_ = state_manager_.UndoOperation(display_buffer_);
            UpdateScratch();
            BaseGfxApp::SetWindowDimensions(display_buffer_->width(),
                                            display_buffer_->height());
            break;
        case UICtrl::UI_REDO:
            display_buffer_ = state_manager_.RedoOperation(display_buffer_);
            UpdateScratch();
            BaseGfxApp::SetWindowDimensions(display_buffer_->width(),
                                            display_buffer_->height());
            break;
        default:
            break;
    }

    update_colors();

    if (control_id >= UICtrl::UI_APPLY_BLUR &&
        control_id <= UICtrl::UI_APPLY_SPECIAL_FILTER) {
        tmp = display_buffer_;
        display_buffer_ = scratch_buffer_;
        scratch_buffer_ = tmp;
        state_manager_.Save(display_buffer_);
    }

    // Forces canvas to update changes made in this function
    glui()->post_update_main_gfx();
}

/*******************************************************************************
 * Member Functions For Managing GLUI Interface
 ******************************************************************************/
void FlashPhotoApp::update_colors(void) {
    glui_ctrl_hooks_.spinner_blue->set_float_val(cur_color_blue_);
    glui_ctrl_hooks_.spinner_green->set_float_val(cur_color_green_);
    glui_ctrl_hooks_.spinner_red->set_float_val(cur_color_red_);
    current_color_.red(cur_color_red_);
    current_color_.green(cur_color_green_);
    current_color_.blue(cur_color_blue_);
}

void FlashPhotoApp::InitGraphics(void) {
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
