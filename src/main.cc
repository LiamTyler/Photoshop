/*******************************************************************************
 * Name            : main.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Do ALL THE THINGS!
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/brushwork_app.h"
#include "include/color_data.h"
#include "include/tool.h"

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int argc, char* argv[]) {
  image_tools::BrushWorkApp *app = new image_tools::BrushWorkApp(800, 800);
  app->Init(argc, argv, 50, 50,
            image_tools::ColorData(1, 1, static_cast<float>(0.95)));

  // runMainLoop returns when the user closes the graphics window.
  app->RunMainLoop();
  delete app;
  exit(0);
}
