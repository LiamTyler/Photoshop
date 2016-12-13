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
   * @return A pointer to the new PixelBuffer to display
   */
  PixelBuffer* Redo(PixelBuffer* display);

  /**
   * @brief Loads the previous action saved into the specified PixelBuffer
   *
   * If there is a previous action saved, it will load it into the specified
   * buffer, resizing as needed. Undo is possible as long as you haven't
   * Undo'ed all the way to the original image, or Undo'ed possible_saves - 1
   * times already.
   *
   * @param[out] display The buffer to load the previous action into
   *
   * @return A pointer to the new PixelBuffer to display
   */
  PixelBuffer* Undo(PixelBuffer* display);
  void SaveCanvas(PixelBuffer* buff);
  void Init(PixelBuffer* blankCanvas);
  bool cant_undo();
  bool cant_redo();

 private:
  HistoryManager(const HistoryManager& h) = delete;
  HistoryManager& operator=(const HistoryManager& h) = delete;
  PixelBuffer** saved_buffers_;  //< The array that saves the PixelBuffer* 's
  PixelBuffer* ResizeAndCopy(PixelBuffer* display);
  int possible_saves_;  //< Maximum number of images that can be saved
  int current_save_;  //< Index of the current save
  int oldest_save_;  //< Index of the oldest save
  int newest_save_;  //< Index of the newest save
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_HISTORY_MANAGER_H_
