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

/**
 * @brief Class for handling the undo / redo features
 *
 * By default it stores the PixelBuffers of the last 80 actions.
 * It will not allow and redos past the most recent, no undos past the oldest
 */
class HistoryManager {
 public:
  HistoryManager(PixelBuffer* buff, int possible_saves);
  ~HistoryManager();
  /**
   * @brief Loads the next action saved into the specified PixelBuffer
   *
   * If there is a next action saved, it will load it into the specified
   * buffer, resizing as needed. Given a series of undos, and then a new
   * action, redo will not change anything because the "branch" of saved
   * actions has been broken.
   *
   * @param[out] display The buffer to load the next action into
   *
   * @return The
   */
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
