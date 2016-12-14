/*******************************************************************************
 * Name            : flashphoto_filter_manager.cc
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Implementation of FlashPhotoFilterManager class
 * Copyright       : 2016 Group Bits Please
 * Creation Date   : 12/14/16
 * Original Author : Liam Tyler
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/FlashPhoto/src/include/flashphoto_filter_manager.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FlashPhotoFilterManager::FlashPhotoFilterManager(void) :
    FilterManager() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
GLUI_Panel* FlashPhotoFilterManager::InitGlui(const GLUI *const glui,
                             void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *filter_panel = new GLUI_Panel(const_cast<GLUI*>(glui), "Filters");
  {
    AddBlurToGLUI(filter_panel, s_gluicallback);
    AddMotionBlurToGLUI(filter_panel, s_gluicallback);
    AddSharpenToGLUI(filter_panel, s_gluicallback);
    AddEdgeDetectToGLUI(filter_panel, s_gluicallback);
    AddThresholdToGLUI(filter_panel, s_gluicallback);
    new GLUI_Column(filter_panel, true);
    AddSaturationToGLUI(filter_panel, s_gluicallback);
    AddChannelToGLUI(filter_panel, s_gluicallback);
    AddQuantizationToGLUI(filter_panel, s_gluicallback);
    AddEmbossToGLUI(filter_panel, s_gluicallback);
  }

  return filter_panel;
} /* FlashPhotoFilterManager::InitGlui() */

}  /* namespace image_tools */
