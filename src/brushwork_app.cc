/*******************************************************************************
 * Name            : brushwork_app.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWrok
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/brushwork_app.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/tool.h"
#include "include/pen.h"
#include "include/caligraphy.h"
#include "include/highlighter.h"
#include "include/rainbow.h"
#include "include/spray_can.h"
#include "include/eraser.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
BrushWorkApp::BrushWorkApp(int width,
                           int height)
    : BaseGfxApp(width,
                 height),
      display_buffer_(nullptr),
      cur_tool_index_(0.0),
      cur_color_red_(0.0),
      cur_color_green_(0.0),
      cur_color_blue_(0.0),
      spinner_r_(nullptr),
      spinner_g_(nullptr),
      spinner_b_(nullptr) {
          tool_select_[0] = new Pen();
          tool_select_[1] = new Eraser();
          tool_select_[2] = new SprayCan();
          tool_select_[3] = new Caligraphy();
          tool_select_[4] = new Highlighter();
          tool_select_[5] = new Rainbow();
          cur_tool_ = tool_select_[0];
          last_x_ = -1;
          last_y_ = -1;
     }

BrushWorkApp::~BrushWorkApp(void) {
    if (display_buffer_) {
        delete display_buffer_;
    }

    for (int i = 0; i < 6; i++) {
        delete tool_select_[i];
    }
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void BrushWorkApp::Init(
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
    set_caption("BrushWork");

    // Initialize Interface
    InitializeBuffers(background_color, width(), height());

    InitGlui();
    InitGraphics();
}

void BrushWorkApp::Display(void) {
    DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

void BrushWorkApp::MouseDragged(int x, int y) {
    if (last_x_ != -1) {
        /* Find the distance between (last_x_, last_y_) and (x, y) and divide by
        an eigth of the width of the mask to determine the number n times to
        ApplyTool between (last_x_, last_y_) and (x, y) */
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

void BrushWorkApp::MouseMoved(int x, int y) {}

void BrushWorkApp::LeftMouseDown(int x, int y) {
    std::cout << "mousePressed " << x << " " << y << std::endl;

    cur_tool_->ApplyTool(display_buffer_, current_color_, x, y,
                         last_x_, last_y_);
    last_x_ = x;
    last_y_ = y;
}

void BrushWorkApp::LeftMouseUp(int x, int y) {
    /* Whenever mouse is released, set last_x_ and last_y_ to -1 so
    last_x_ and last_y_ don't get connected to the new x and y the next
    time the mouse is dragged */
    last_x_ = -1;
    last_y_ = -1;
    std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void BrushWorkApp::InitializeBuffers(
    ColorData background_color,
    int width,
    int height) {
    display_buffer_ = new PixelBuffer(width, height, background_color);
}

void BrushWorkApp::update_current_color() {
    current_color_.red(cur_color_red_);
    current_color_.green(cur_color_green_);
    current_color_.blue(cur_color_blue_);
}

ColorData BrushWorkApp::get_current_color() {
    return current_color_;
}

void BrushWorkApp::InitGlui(void) {
    // Select first tool (this activates the first radio button in glui)
    cur_tool_index_ = 0;

    GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel,
                                                 &cur_tool_index_,
                                                 UI_TOOLTYPE,
                                                 s_gluicallback);

    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Eraser");
    new GLUI_RadioButton(radio, "Spray Can");
    new GLUI_RadioButton(radio, "Caligraphy Pen");
    new GLUI_RadioButton(radio, "Highlighter");
    new GLUI_RadioButton(radio, "Rainbow");

    GLUI_Panel *color_panel = new GLUI_Panel(glui(), "Tool Color");

    cur_color_red_ = 0;
    spinner_r_  = new GLUI_Spinner(color_panel, "Red:", &cur_color_red_,
                                   UI_COLOR_R, s_gluicallback);
    spinner_r_->set_float_limits(0, 1.0);

    cur_color_green_ = 0;
    spinner_g_ = new GLUI_Spinner(color_panel, "Green:", &cur_color_green_,
                                   UI_COLOR_G, s_gluicallback);
    spinner_g_->set_float_limits(0, 1.0);

    cur_color_blue_ = 0;
    spinner_b_  = new GLUI_Spinner(color_panel, "Blue:", &cur_color_blue_,
                                   UI_COLOR_B, s_gluicallback);
    this->update_current_color();
    spinner_b_->set_float_limits(0, 1.0);
    new GLUI_Button(color_panel, "Red", UI_PRESET_RED, s_gluicallback);
    new GLUI_Button(color_panel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
    new GLUI_Button(color_panel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
    new GLUI_Button(color_panel, "Green", UI_PRESET_GREEN, s_gluicallback);
    new GLUI_Button(color_panel, "Blue", UI_PRESET_BLUE, s_gluicallback);
    new GLUI_Button(color_panel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
    new GLUI_Button(color_panel, "White", UI_PRESET_WHITE, s_gluicallback);
    new GLUI_Button(color_panel, "Black", UI_PRESET_BLACK, s_gluicallback);


    new GLUI_Button(glui(), "Quit", UI_QUIT, static_cast<GLUI_Update_CB>(exit));
}


void BrushWorkApp::InitGraphics(void) {
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

void BrushWorkApp::GluiControl(int control_id) {
    switch (control_id) {
    case UI_PRESET_RED:
        cur_color_red_ = 1;
        cur_color_green_ = 0;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_ORANGE:
        cur_color_red_ = 1;
        cur_color_green_ = 0.5;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_YELLOW:
        cur_color_red_ = 1;
        cur_color_green_ = 1;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_GREEN:
        cur_color_red_ = 0;
        cur_color_green_ = 1;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_BLUE:
        cur_color_red_ = 0;
        cur_color_green_ = 0;
        cur_color_blue_ = 1;
        break;
    case UI_PRESET_PURPLE:
        cur_color_red_ = 0.5;
        cur_color_green_ = 0;
        cur_color_blue_ = 1;
        break;
    case UI_PRESET_WHITE:
        cur_color_red_ = 1;
        cur_color_green_ = 1;
        cur_color_blue_ = 1;
        break;
    case UI_PRESET_BLACK:
        cur_color_red_ = 0;
        cur_color_green_ = 0;
        cur_color_blue_ = 0;
        break;
    case UI_TOOLTYPE:
        cur_tool_ = tool_select_[cur_tool_index_];
    default:
        break;
    }

    this->update_current_color();

    spinner_b_->set_float_val(cur_color_blue_);
    spinner_g_->set_float_val(cur_color_green_);
    spinner_r_->set_float_val(cur_color_red_);
}
}  // namespace image_tools
