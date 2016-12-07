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
#include <iomanip>
#include <string>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/imgtools_interface.h"
#include "lib/libimgtools/src/include/image_handler.h"

using image_tools::PixelBuffer;
using std::cout;
using std::endl;

CmdLineHandler::CmdLineHandler() :
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
    commands_(),
    invalids_() {}

void CmdLineHandler::ParseArguments(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h")) {
            commands_.push_back(CmdLineHandler::HELP);
        } else if (!strcmp(argv[i], "-sharpen")) {
            commands_.push_back(CmdLineHandler::SHARPEN);
            sharpen_amt_ = atof(argv[++i]);
        } else if (!strcmp(argv[i], "-edge")) {
            commands_.push_back(CmdLineHandler::EDGE);
        } else if (!strcmp(argv[i], "-threshhold")) {
            commands_.push_back(CmdLineHandler::THRESHOLD);
            threshold_amt_ = atof(argv[++i]);
        } else if (!strcmp(argv[i], "-quantize")) {
            commands_.push_back(CmdLineHandler::QUANTIZE);
            quantize_amt_ = atof(argv[++i]);
        } else if (!strcmp(argv[i], "-blur")) {
            commands_.push_back(CmdLineHandler::BLUR);
            blur_amt_ = atof(argv[++i]);
        } else if (!strcmp(argv[i], "-saturate")) {
            commands_.push_back(CmdLineHandler::SATURATE);
            saturate_amt_ = atof(argv[++i]);
        } else if (!strcmp(argv[i], "-channel")) {
            commands_.push_back(CmdLineHandler::CHANNEL);
            channel_red_amt_ = atof(argv[++i]);
            channel_green_amt_ = atof(argv[++i]);
            channel_blue_amt_ = atof(argv[++i]);
        } else if (!strcmp(argv[i], "-compare")) {
            commands_.push_back(CmdLineHandler::COMPARE);
        } else if (input_file_ == "" && ImageHandler::GetImageType(argv[i])
                != ImageHandler::UNKNOWN_IMAGE) {
            input_file_ = argv[i];
        } else if (input_file_ != "" && output_file_ == ""
                && ImageHandler::GetImageType(argv[i]) !=
                ImageHandler::UNKNOWN_IMAGE) {
            output_file_ = argv[i];
        } else {
            invalids_.push_back(argv[i]);
        }
    }
}

int CmdLineHandler::RunCommands() {
    int invalids_size = invalids_.size();
    if (invalids_size != 0) {
        for (int i = 0; i < invalids_size; i++) {
            cout << "Unknown argument: " << invalids_[i] << endl;
        }
        return 1;
    }
    // Load up the input image first
    if (input_file_ != "") {
        if (ImageHandler::GetImageType(input_file_) !=
                ImageHandler::UNKNOWN_IMAGE) {
            in_img_ = ImageHandler::LoadImage(input_file_);
            if (in_img_ == nullptr) {
                return 1;
            } else {
                int w = in_img_->width();
                int h = in_img_->height();
                out_img_ = new PixelBuffer(w, h,
                        in_img_->background_color());
            }
        }
    } else {
        return 1;
    }

    // Process commands one at a time in order of appearance
    int commands_size = commands_.size();
    for (int i = 0; i < commands_size; i++) {
        bool swap = true;
        switch (commands_[i]) {
            case CmdLineHandler::HELP:
                cout << "usage: MIA\t[input_image] [-sharpen float] [-edge]"
                    << "\n\t\t[-threshold float] [-quantize int] [-blur float]"
                    << "\n\t\t[-saturate float] [-channel float float float]\n"
                    << "\t\t [-compare] [output / compare image]"
                    << endl << endl;
                swap = false;
                break;
            case CmdLineHandler::SHARPEN:
                imgtools::ApplySharpen(in_img_, out_img_, sharpen_amt_);
                break;
            case CmdLineHandler::EDGE:
                imgtools::ApplyEdgeDetect(in_img_, out_img_);
                break;
            case CmdLineHandler::THRESHOLD:
                imgtools::ApplyThreshold(in_img_, out_img_,
                        threshold_amt_);
                break;
            case CmdLineHandler::QUANTIZE:
                imgtools::ApplyQuantize(in_img_, out_img_, quantize_amt_);
                break;
            case CmdLineHandler::BLUR:
                imgtools::ApplyBlur(in_img_, out_img_, blur_amt_);
                break;
            case CmdLineHandler::SATURATE:
                imgtools::ApplySaturate(in_img_, out_img_, saturate_amt_);
                break;
            case CmdLineHandler::CHANNEL:
                imgtools::ApplyChannel(in_img_, out_img_, channel_red_amt_,
                        channel_green_amt_, channel_blue_amt_);
                break;
            case CmdLineHandler::COMPARE:
                // delete out_img_;
                // out_img_ = imgtools::LoadImage(output_file_);
                // int ret = imgtools::ApplyCompare(in_img_, out_img_);
                // delete in_img_;
                // delete out_img_;
                // return ret;
                swap = false;
                break;
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
    int ret = 0;
    if (!imgtools::SaveImage(output_file_, in_img_))
        ret = 1;

    delete in_img_;
    delete out_img_;

    return ret;
}

void CmdLineHandler::PrintInfo() {
    // cout << "Input image: " << input_file_ << endl;
    cout << "Output image: " << output_file_ << endl;
    int invalids_size = invalids_.size();
    for (int i = 0; i < invalids_size; i++) {
        cout << "Unknown argument: " << invalids_[i] << endl;
    }
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
