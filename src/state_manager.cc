/*******************************************************************************
 * Name            : state_manager.cc
 * Project         : FlashPhoto
 * Module          : state_manager
 * Description     : Implementation of StateManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Sun Oct 2 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/state_manager.h"
#include <iostream>
#include "include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
StateManager::StateManager(void) :
    history_(nullptr),
    undo_btn_(nullptr),
    redo_btn_(nullptr) {}

StateManager::~StateManager(void) {
    delete history_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void StateManager::InitGlui(const GLUI *const glui,
                            void (*s_gluicallback)(int),
                            PixelBuffer* display) {
  history_ = new HistoryManager(display, 80);
  undo_btn_ = new GLUI_Button(const_cast<GLUI*>(glui), "Undo", UICtrl::UI_UNDO,
                              s_gluicallback);
  undo_toggle(false);

  redo_btn_  = new GLUI_Button(const_cast<GLUI*>(glui), "Redo", UICtrl::UI_REDO,
                               s_gluicallback);
  redo_toggle(false);
}

void StateManager::Save(PixelBuffer* display) {
    history_->SaveCanvas(display);
    if (history_->cant_redo())
        redo_toggle(false);
    if (!history_->cant_undo())
        undo_toggle(true);
}

PixelBuffer* StateManager::UndoOperation(PixelBuffer* display) {
  std::cout << "Undoing..." << std::endl;
  PixelBuffer* tmp = history_->Undo(display);
  if (history_->cant_undo())
      undo_toggle(false);

  redo_toggle(true);

  return tmp;
}

PixelBuffer* StateManager::RedoOperation(PixelBuffer* display) {
  std::cout << "Redoing..." << std::endl;
  PixelBuffer* tmp = history_->Redo(display);
  if (history_->cant_redo())
      redo_toggle(false);

  undo_toggle(true);

  return tmp;
}

}  /* namespace image_tools */
