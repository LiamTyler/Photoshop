/*******************************************************************************
 * Name            : history_manager.cc
 * Project         : FlashPhoto
 * Module          : history_manager
 * Description     : CC for HistoryManager class
 * Copyright       : Group Bits Please
 * Creation Date   : 11/18/2016
 * Original Author : Liam Tyler + Jess Henderson
 *
 ******************************************************************************/

#include "include/history_manager.h"
#include "include/color_data.h"

using image_tools::ColorData;
using image_tools::PixelBuffer;

HistoryManager::HistoryManager(PixelBuffer* buff, int possible_saves) :
                                saved_buffers_(nullptr),
                                possible_saves_(possible_saves),
                                current_save_(-1),
                                oldest_save_(0),
                                newest_save_(0) {
    Init(buff);
}

HistoryManager::~HistoryManager() {
    for (int i = 0; i < possible_saves_; i++)
        delete saved_buffers_[i];
    delete[] saved_buffers_;
}

void HistoryManager::Init(PixelBuffer* buff) {
    saved_buffers_ = new PixelBuffer*[possible_saves_];
    for (int i = 0; i < possible_saves_; i++)
        saved_buffers_[i] = nullptr;

    SaveCanvas(buff);
    oldest_save_ = 0;
}

void HistoryManager::SaveCanvas(PixelBuffer* buff) {
    // Update the positions
    current_save_ = (current_save_ + 1) % possible_saves_;
    newest_save_ = current_save_;
    if (current_save_ == oldest_save_)
        oldest_save_ = (oldest_save_ + 1) % possible_saves_;

    int width = buff->width();
    int height = buff->height();
    ColorData bg = buff->background_color();
    PixelBuffer* curr = saved_buffers_[current_save_];
    // Delete the current pixelbuffer in this spot if there is and old one,
    // and it is of different size than the new one
    if (curr != nullptr) {
        if (width != curr->width() || height != curr->height()) {
            delete curr;
            curr = new PixelBuffer(width, height, bg);
        } else {
            curr->set_background_color(bg);
        }
    } else {
        curr = new PixelBuffer(width, height, bg);
    }

    std::cout << "buff h: " << height << ", buff w: " << width <<
    ", curr h: " << curr->height() << ", curr w: "
    << curr->width() << std::endl;

    // Copy the actual pixels over into the buffer, now that it has the
    // correct size and bg color
    for (int r = 0; r < height; r++)
        for (int c = 0; c < width; c++)
            curr->set_pixel(c, r, buff->get_pixel(c, r));
    saved_buffers_[current_save_] = curr;
}

PixelBuffer* HistoryManager::Redo(PixelBuffer* display) {
    // Check to see if we can even redo
    if (current_save_ == newest_save_)
        return display;

    current_save_ = (current_save_ + 1) % possible_saves_;
    return ResizeAndCopy(display);
}

PixelBuffer* HistoryManager::Undo(PixelBuffer* display) {
    // Check to see if we can even redo
    if (current_save_ == oldest_save_)
        return display;

    current_save_ = (current_save_ - 1) % possible_saves_;
    return ResizeAndCopy(display);
}

PixelBuffer* HistoryManager::ResizeAndCopy(PixelBuffer* display) {
    int d_height = display->height();
    int d_width = display->width();
    PixelBuffer* curr = saved_buffers_[current_save_];
    int c_height = curr->height();
    int c_width = curr->width();
    ColorData bg = curr->background_color();

    // Check to see if current display is the same dimensions
    // as the saved one. If so, no need to resize it.
    if (c_width != d_width || c_height == d_height) {
        delete display;
        display = new PixelBuffer(c_width, c_height, bg);
    }

    // Now copy the saved buff into the display one
    for (int r = 0; r < c_height; r++)
        for (int c = 0; c < c_width; c++)
            display->set_pixel(c, r, curr->get_pixel(c, r));

    return display;
}

bool HistoryManager::cant_undo() {
    if (current_save_ == oldest_save_)
        return true;

    return false;
}

bool HistoryManager::cant_redo() {
    if (current_save_ == newest_save_)
        return true;

    return false;
}
