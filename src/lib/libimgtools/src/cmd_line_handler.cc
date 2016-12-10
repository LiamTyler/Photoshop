/*******************************************************************************
 * Name            : cmd_line_handler.cc
 * Project         : libimgtools
 * Module          : CmdLineHandler
 * Description     : Handle commands done through the command line
 * Copyright       : Group Bits Please
 * Creation Date   : 12/6/16
 * Original Author : Liam Tyler
 *
 ******************************************************************************/

#include "lib/libimgtools/src/include/cmd_line_handler.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <regex>
#include <iomanip>
#include <string>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/imgtools_interface.h"
#include "lib/libimgtools/src/include/image_handler.h"

using image_tools::PixelBuffer;
using std::cout;
using std::endl;

CmdLineHandler::CmdLineHandler(int argc, char** argv) :
    argc_(argc),
    argv_(argv),
    current_arg_(1),
    sharpen_amt_(0),
    threshold_amt_(0),
    quantize_amt_(0),
    blur_amt_(0),
    saturate_amt_(0),
    channel_red_amt_(0),
    channel_green_amt_(0),
    channel_blue_amt_(0),
    input_file_(""),
    output_file_(""),
    in_img_(nullptr),
    out_img_(nullptr),
    commands_() {}

CmdLineHandler::Command CmdLineHandler::get_index(const char* arg) {
    Command ret;
    if (!strcmp(arg, "-h")) {
        ret = HELP;
    } else if (!strcmp(arg, "-sharpen")) {
        ret = SHARPEN;
    } else if (!strcmp(arg, "-edge")) {
        ret = EDGE;
    } else if (!strcmp(arg, "-threshold")) {
        ret = THRESHOLD;
    } else if (!strcmp(arg, "-quantize")) {
        ret = QUANTIZE;
    } else if (!strcmp(arg, "-blur")) {
        ret = BLUR;
    } else if (!strcmp(arg, "-saturate")) {
        ret = SATURATE;
    } else if (!strcmp(arg, "-channel")) {
        ret = CHANNEL;
    } else if (!strcmp(arg, "-compare")) {
        ret = COMPARE;
    } else if (ImageHandler::GetImageType(arg) != ImageHandler::UNKNOWN_IMAGE) {
        ret = IMAGE;
    } else {
        ret = ARG;
    }
    return ret;
}

/**
 * @brief Checks to see if the arguments exist and are numbers.
 *
 * Does NOT check to see if the numbers are within the valid ranges
 * for the command.
 *
 * @param[in] index The current position we are into argv_
 * @param[in] command The CmdLineHandler enum of the command
 *
 * @return true if arguments exist and are valid, false if not
 */
bool CmdLineHandler::ValidateArgs(int index, Command command) {
    // Find the expected number of arguments for the command
    int expected_args;
    switch(command) {
        case SHARPEN:
            expected_args = 1;
            break;
        case EDGE:
            expected_args = 0;
            break;
        case THRESHOLD:
            expected_args = 1;
            break;
        case QUANTIZE:
            expected_args = 1;
            break;
        case BLUR:
            expected_args = 1;
            break;
        case SATURATE:
            expected_args = 1;
            break;
        case CHANNEL:
            expected_args = 3;
            break;
        case COMPARE:
            expected_args = 0;
            break;
        case IMAGE:
            expected_args = 0;
            break;
        default:
            break;
    }

    if (expected_args == 0)
        return true;

    for (int arg = 0; arg < expected_args; arg++) {
        // If there are no mare args to process, but we are expecting more,
        // signal error
        if (index + arg >= argc_)
            return false;
        // If we run into a new command before we are done processing
        // the expected number of args, signal error
        if (get_index(argv_[index + arg]) != ARG)
            return false;
        // If the arg is not a number, signal error
        if (!is_number(argv_[index + arg]))
            return false;
    }

    return true;
}

bool CmdLineHandler::is_number(const char* arg) {
    std::regex e ("^-?\\d*\\.?\\d+");
    if (std::regex_match(arg, e))
        return true;
    else
        return false;
}

bool CmdLineHandler::ParseArguments() {
    for (; current_arg_ < argc_; current_arg_++) {
        Command index = get_index(argv_[current_arg_]);
        cout << "curr index: " << index << endl;
        if (index == ARG)
            return false;

        // Test to see if the arguments exist and are numbers
        if (!ValidateArgs(current_arg_ + 1, index))
            return false;
        cout << "made it past validate args" << endl;

        // Find if the arguments actually fall within the acceptable ranges
        switch(index) {
            case HELP:
                break;
            case SHARPEN:
                sharpen_amt_ = atof(argv_[++current_arg_]);
                if (!(0.0 <= sharpen_amt_ && sharpen_amt_ <= 100.0))
                    return false;
                break;
            case EDGE:
                break;
            case THRESHOLD:
                threshold_amt_ = atof(argv_[++current_arg_]);
                if (!(0.0 <= threshold_amt_ && threshold_amt_ <= 1.0))
                    return false;
                break;
            case QUANTIZE:
                quantize_amt_ = atoi(argv_[++current_arg_]);
                if (!(2 <= quantize_amt_ && quantize_amt_ <= 256))
                    return false;
                break;
            case BLUR:
                blur_amt_ = atof(argv_[++current_arg_]);
                if (!(0.0 <= blur_amt_ && blur_amt_ <= 20.0))
                    return false;
                break;
            case SATURATE:
                saturate_amt_ = atof(argv_[++current_arg_]);
                if (!(-10.0 <= saturate_amt_ && saturate_amt_ <= 10.0))
                break;
            case CHANNEL:
                channel_red_amt_ = atof(argv_[++current_arg_]);
                channel_green_amt_ = atof(argv_[++current_arg_]);
                channel_blue_amt_ = atof(argv_[++current_arg_]);
                if (!(0 <= channel_red_amt_ && channel_red_amt_ <= 10.0 &&
                      0 <= channel_green_amt_ && channel_green_amt_ <= 10.0 &&
                      0 <= channel_blue_amt_ && channel_blue_amt_ <= 10.0))
                    return false;
                break;
            case COMPARE:
                break;
            case IMAGE:
                if (current_arg_ == 1) 
                    input_file_ = argv_[current_arg_];
                else if (current_arg_ == argc_ - 1 && input_file_ != "")
                    output_file_ = argv_[current_arg_];
                else
                    return false;
                break;
            default:
                break;
        }
        if (index != IMAGE)
            commands_.push_back(index);
    }
    return true;
}

bool CmdLineHandler::RunCommands() {
    // Load up the input image first
    if (input_file_ != "") {
        if (ImageHandler::GetImageType(input_file_) !=
                ImageHandler::UNKNOWN_IMAGE) {
            in_img_ = ImageHandler::LoadImage(input_file_);
            if (in_img_ == nullptr) {
                return false;
            } else {
                int w = in_img_->width();
                int h = in_img_->height();
                out_img_ = new PixelBuffer(w, h,
                        in_img_->background_color());
            }
        }
    } else {
        return false;
    }

    // Process commands one at a time in order of appearance
    int commands_size = commands_.size();
    for (int i = 0; i < commands_size; i++) {
        bool swap = true;
        switch (commands_[i]) {
            case HELP:
                cout << "usage: MIA\t[input_image] [-sharpen float] [-edge]"
                    << "\n\t\t[-threshold float] [-quantize int] [-blur float]"
                    << "\n\t\t[-saturate float] [-channel float float float]\n"
                    << "\t\t [-compare] [output / compare image]"
                    << endl << endl;
                swap = false;
                break;
            case SHARPEN:
                imgtools::ApplySharpen(in_img_, out_img_, sharpen_amt_);
                break;
            case EDGE:
                imgtools::ApplyEdgeDetect(in_img_, out_img_);
                break;
            case THRESHOLD:
                imgtools::ApplyThreshold(in_img_, out_img_,
                        threshold_amt_);
                break;
            case QUANTIZE:
                imgtools::ApplyQuantize(in_img_, out_img_, quantize_amt_);
                break;
            case BLUR:
                imgtools::ApplyBlur(in_img_, out_img_, blur_amt_);
                break;
            case SATURATE:
                imgtools::ApplySaturate(in_img_, out_img_, saturate_amt_);
                break;
            case CHANNEL:
                imgtools::ApplyChannel(in_img_, out_img_, channel_red_amt_,
                        channel_green_amt_, channel_blue_amt_);
                break;
            case COMPARE:
                {
                    delete out_img_;
                    out_img_ = imgtools::LoadImage(output_file_);
                    int ret = imgtools::CompareImages(in_img_, out_img_);
                    cout << ret << endl;
                    delete in_img_;
                    delete out_img_;
                    return ret;
                }
            default:
                swap = false;
                cout << "unrecognized switch case" << endl;
        }
        if (swap) {
            PixelBuffer* tmp = in_img_;
            in_img_ = out_img_;
            out_img_ = tmp;
        }
    }
    // Output the image created
    bool ret = true;
    if (!imgtools::SaveImage(output_file_, in_img_))
        ret = false;

    delete in_img_;
    delete out_img_;

    return ret;
}

bool CmdLineHandler::ProcessArguments() {
    if (!ParseArguments()) {
        cout << "parsing args failed" << endl;
        return false;
    }
    if (!RunCommands()) {
        cout << "running commands failed" << endl;
        return false;
    }

    return true;
}

void CmdLineHandler::PrintInfo() {
    // cout << "Input image: " << input_file_ << endl;
    cout << "Output image: " << output_file_ << endl;
    int commands_size = commands_.size();
    for (int i = 0; i < commands_size; i++) {
        cout << "Command " << i + 1 << ": " << commands_[i] << endl;
    }
    cout << "Sharpen amt: " << sharpen_amt_ << endl;
    cout << "Threshold amt: " << sharpen_amt_ << endl;
    cout << "Quantize amt: " << sharpen_amt_ << endl;
    cout << "Blur amt: " << sharpen_amt_ << endl;
    cout << "Saturate amt: " << sharpen_amt_ << endl;
    cout << "Channel red amt: " << channel_red_amt_ << endl;
    cout << "Channel green amt: " << channel_green_amt_ << endl;
    cout << "Channel blue amt: " << channel_blue_amt_ << endl;
}
