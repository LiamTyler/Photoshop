/*******************************************************************************
 * Name            : cmd_line_handler.cc
 * Project         : libimgtools
 * Module          : CmdLineHandler
 * Description     : Handle commands done through the command line
 * Copyright       : Group Bits Please
 * Creation Date   : 12/6/16
 * Original Author : Liam Tyler
 *
 ******************************************************************************/

#include "lib/libimgtools/src/include/cmd_line_handler.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/imgtools_interface.h"
#include "lib/libimgtools/src/include/image_handler.h"

using image_tools::PixelBuffer;
using std::cout;
using std::endl;

CmdLineHandler::CmdLineHandler() : input_file_(""),
    output_file_(""),
    in_img_(nullptr),
    scratch_img_(nullptr),
    commands_() {}

void CmdLineHandler::ParseArguments(int argc, char* argv[]) {
    /*
    PixelBuffer* img = nullptr;
    PixelBuffer* scratch = nullptr;
    PixelBuffer* tmp;
    bool in = false;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h")) {
            cout << "-h command" << endl;
        } else if (!strcmp(argv[i], "-sharpen")) {
            float amt = atof(argv[++i]);
            cout << "-sharpen command with amount: " << amt << endl;
            imgtools::ApplySharpen(img, scratch, amt);
            tmp = img;
            img = scratch;
            scratch = tmp;
        } else if (!strcmp(argv[i], "-edge")) {
            cout << "-edge command " << endl;
            imgtools::ApplyEdgeDetect(img, scratch);
            tmp = img;
            img = scratch;
            scratch = tmp;
        } else if (!in && ImageHanlder::GetImageType(argv[i]) != UNKNOWN_IMAGE) {
            img = imgtools::LoadImage(argv[i]);
            int w = img->width();
            int h = img->height();
            scratch = new PixelBuffer(w, h, img->background_color());
            in = true;
        } else if (in && ImageHanlder::GetImageType(argv[i]) != UNKNOWN_IMAGE) {
            cout << "about to save" << endl;
            if (imgtools::SaveImage(argv[i], img))
                cout << "Saved img" << endl;
            else
                cout << "Failed to save img" << endl;
        } else {
            cout << "Non registered command: " << argv[i] << endl;
        }
    }
    if (img != nullptr) {
        delete img;
        delete tmp;
    }
    */
}

void CmdLineHandler::RunCommands() {

}
