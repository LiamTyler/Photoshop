/*******************************************************************************
 * Name            : state_manager.h
 * Project         : FlashPhoto
 * Module          : state_manager
 * Description     : Header for IoHandler class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_STATE_MANAGER_H_
#define SRC_INCLUDE_STATE_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "GL/glui.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/history_manager.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The manager for simulation state in FlashPhoto.
 *
 * Simulation state is defined as the sequence of operations that comprises the
 * current canvas. An operation is defined as what happens during 1 click/drag
 * operation, or when 1 button on the control panel that affects the canvas is
 * clicked.
 *
 * A sequence of undos followed by some edits, followed by more undos will
 * FIRST undo the new edits, until you get back to the state before you made the
 * edits. You will not be able to go back any further.
 */
class StateManager {
 public:
  StateManager();
  ~StateManager();

  void InitGlui(const GLUI *const glui,
                void (*s_gluicallback)(int),
                PixelBuffer* display);

  void Save(PixelBuffer* display);

  /**
   * @brief Undoes the last operation applied to the canvas (not permanently; it
   * can still be re-done later)
   *
   */
  PixelBuffer* UndoOperation(PixelBuffer* display);

  /**
   * @brief Re-does the last un-done operation applied to the canvas (not
   * permanently; it can be undone again later)
   *
   */
  PixelBuffer* RedoOperation(PixelBuffer* display);

 private:
  void redo_toggle(bool select) {
    UICtrl::button_toggle(redo_btn_, select);
  }

  void undo_toggle(bool select) {
    UICtrl::button_toggle(undo_btn_, select);
  }

  /* Copy/move assignment/construction disallowed */
  StateManager(const StateManager &rhs) = delete;
  StateManager& operator=(const StateManager &rhs) = delete;

  /* data members */
  HistoryManager *history_;
  GLUI_Button *undo_btn_;
  GLUI_Button *redo_btn_;
};

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_STATE_MANAGER_H_ */
