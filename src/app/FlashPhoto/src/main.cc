/*******************************************************************************
 * Name            : main.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Do ALL THE THINGS!
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 * Modified Author : Liam Tyler
 * Modified Date   : 12/5/16
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include "app/FlashPhoto/src/include/flashphoto_app.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/imgtools_interface.h"
#include "lib/libimgtools/src/include/cmd_line_handler.h"
#include "lib/libimgtools/src/include/image_handler.h"

using image_tools::PixelBuffer;
using std::cout;
using std::endl;


/*******************************************************************************
 * Functions
 ******************************************************************************/
int main(int argc, char* argv[]) {
    if (argc > 1) {
        // process the command line options
        /*
        for (int i = 1; i < argc; i++) {
            std::cout << argv[i] << std::endl;
        }
        */
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
            } else if (!in && ImageHandler::GetImageType(argv[i]) != ImageHandler::UNKNOWN_IMAGE) {
                img = imgtools::LoadImage(argv[i]);
                int w = img->width();
                int h = img->height();
                scratch = new PixelBuffer(w, h, img->background_color());
                in = true;
            } else if (in && ImageHandler::GetImageType(argv[i]) != ImageHandler::UNKNOWN_IMAGE) {
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
    } else {
        image_tools::FlashPhotoApp *app = new image_tools::FlashPhotoApp(800, 800);
        app->Init(argc, argv, 50, 50,
            image_tools::ColorData(1, 1, static_cast<float>(0.95)));
        // runMainLoop returns when the user closes the graphics window.
        app->RunMainLoop();
        delete app;
    }
    exit(0);
}
