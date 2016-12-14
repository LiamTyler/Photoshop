/*******************************************************************************
 * Name            : flashphoto_filter_manager.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for FlashPhotoFilterManager class
 * Copyright       : 2016 Group Bits Please
 * Creation Date   : 12/14/16
 * Original Author : Liam Tyler
 *
 ******************************************************************************/

#ifndef SRC_APP_FLASHPHOTO_SRC_INCLUDE_FLASHPHOTO_FILTER_MANAGER_H_
#define SRC_APP_FLASHPHOTO_SRC_INCLUDE_FLASHPHOTO_FILTER_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/filter_manager.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Manager for all aspects of filters in FlashPhoto, including
 * initialization of GLUI control elements for filters, filter creation,
 * application, deletion.
 */
class FlashPhotoFilterManager : public FilterManager {
 public:
  FlashPhotoFilterManager();

  GLUI_Panel* InitGlui(const GLUI *const glui,
                       void (*s_gluicallback)(int));
};

}  /* namespace image_tools */

#endif  // SRC_APP_FLASHPHOTO_SRC_INCLUDE_FLASHPHOTO_FILTER_MANAGER_H_
