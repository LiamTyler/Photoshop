/*******************************************************************************
 * Name            : mia_filter_manager.cc
 * Project         : MIA
 * Module          : filter_manager
 * Description     : Implementation of MIAFilterManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:47:02 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/MIA/src/include/mia_filter_manager.h"
/* FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIAFilterManager::MIAFilterManager(void) :
    FilterManager() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
GLUI_Panel* MIAFilterManager::InitGlui(const GLUI *const glui,
                             void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *filter_panel = new GLUI_Panel(const_cast<GLUI*>(glui), "Filters");
  {
    AddSharpenToGLUI(filter_panel, s_gluicallback);
    AddEdgeDetectToGLUI(filter_panel, s_gluicallback);
    AddThresholdToGLUI(filter_panel, s_gluicallback);
    AddBlurToGLUI(filter_panel, s_gluicallback);

    new GLUI_Column(filter_panel, true);
    // AddSaturationToGLUI(filter_panel, s_gluicallback);
    {
      GLUI_Panel *satur_panel = new GLUI_Panel(filter_panel, "Grayscale");

      new GLUI_Button(satur_panel, "Apply",
      UICtrl::UI_APPLY_SATURATE,
      s_gluicallback);
    }
    AddChannelToGLUI(filter_panel, s_gluicallback);
    AddQuantizationToGLUI(filter_panel, s_gluicallback);
  }

  return filter_panel;
} /* MIAFilterManager::InitGlui() */

}  /* namespace image_tools */
