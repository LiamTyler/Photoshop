/*******************************************************************************
 * Name            : history_manager.h
 * Project         : FlashPhoto
 * Module          : history_manager
 * Description     : Header for HistoryManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:40:20 2016
 * Original Author : Liam Tyler + Jess Henderson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_HISTORY_MANAGER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_HISTORY_MANAGER_H_

#include "lib/libimgtools/src/include/pixel_buffer.h"

using image_tools::PixelBuffer;

class HistoryManager {
 public:
  HistoryManager(PixelBuffer* buff, int possible_saves);
  ~HistoryManager();
  PixelBuffer* Redo(PixelBuffer* display);
  PixelBuffer* Undo(PixelBuffer* display);
  void SaveCanvas(PixelBuffer* buff);
  void Init(PixelBuffer* blankCanvas);
  bool cant_undo();
  bool cant_redo();

 private:
  HistoryManager(const HistoryManager& h) = delete;
  HistoryManager& operator=(const HistoryManager& h) = delete;
  PixelBuffer** saved_buffers_;
  PixelBuffer* ResizeAndCopy(PixelBuffer* display);
  int possible_saves_;
  int current_save_;
  int oldest_save_;
  int newest_save_;
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_HISTORY_MANAGER_H_
