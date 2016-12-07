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

#include <stdlib.h>
#include <iostream>
#include <iomanip>
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
        CmdLineHandler c;
        c.ParseArguments(argc, argv);
        c.PrintInfo();
        c.RunCommands();
    } else {
        image_tools::FlashPhotoApp *app =
            new image_tools::FlashPhotoApp(800, 800);
        app->Init(argc, argv, 50, 50,
            image_tools::ColorData(1, 1, static_cast<float>(0.95)));
        // runMainLoop returns when the user closes the graphics window.
        app->RunMainLoop();
        delete app;
    }
    exit(0);
}
