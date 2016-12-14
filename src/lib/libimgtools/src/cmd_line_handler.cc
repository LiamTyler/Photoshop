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
#include <dirent.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/imgtools_interface.h"
#include "lib/libimgtools/src/include/image_handler.h"

using image_tools::PixelBuffer;
using std::string;
using std::cout;
using std::endl;

const bool debug = false;

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
    switch (command) {
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
        if (debug)
            cout << "arg " << arg << " = " << argv_[arg + index] << endl;
        // If there are no mare args to process, but we are expecting more,
        // signal error
        if (index + arg >= argc_) {
            if (debug)
                cout << "too many args" << endl;
            return false;
        }
        // If we run into a new command before we are done processing
        // the expected number of args, signal error
        Command tmp;
        if ((tmp = get_index(argv_[index + arg])) != ARG) {
            if (debug)
                cout << "too few args, command = " << tmp << endl;
            return false;
        }
        // If the arg is not a number, signal error
        if (!is_number(argv_[index + arg])) {
            if (debug)
                cout << "arg is not a number" << endl;
            return false;
        }
    }

    return true;
}

bool CmdLineHandler::is_number(const char* arg) {
    char *p;
    double d = strtod(arg, &p);
    if (*p)
        return false;
    else
        return true;
}

bool CmdLineHandler::ParseArguments() {
    for (; current_arg_ < argc_; current_arg_++) {
        Command index = get_index(argv_[current_arg_]);
        // cout << "curr index: " << index << endl;
        if (index == ARG) {
            if (debug)
                cout << "index == arg, command = " << argv_[current_arg_]
                    << endl;
            return false;
        }

        // Test to see if the arguments exist and are numbers
        if (!ValidateArgs(current_arg_ + 1, index)) {
            if (debug)
                cout << "Failed on validate args with command: " <<
                    index << endl;
            return false;
        }

        // Find if the arguments actually fall within the acceptable ranges
        switch (index) {
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

void CmdLineHandler::PrintHelp() {
    cout << endl << "usage: MIA [input_image_name] [list of commands] "
        << "[output_image_name]" << endl
        << "Commands:" << endl
        << "--------------------------------------------------------------\n"
        << "-sharpen\tArguments: 1, type: float, valid inputs: [0, 100]\n"
        << "-edge\t\tArguments: 0\n"
        << "-threshold\tArguments: 1, type: float, valid inputs: [0, 1]\n"
        << "-quantize\tArguments: 1, type: int, valid inputs: [2, 256]\n"
        << "-blur\t\tArguments: 1, type: float, valid inputs: [0, 20]\n"
        << "-saturate\tArguments: 1, type: float, valid inputs: [-10, 10]\n"
        << "-channel\tArguments: 3, type: float float float, "
            << "valid inputs: [0, 10] [0, 10] [0, 10]\n"
        << "-compare\tArguments: 1 type: compare_image"
            << "(instead of output image)\n"
        << endl;
}

bool CmdLineHandler::RunCommands() {
    // Create list of images to process (can be more than one if using
    // ### to signify a 'stack' of images
    std::vector<std::string> images;

    string s = input_file_;
    string directory = "./";
    string fname = input_file_;
    DIR *d;
    struct dirent *dir;
    std::size_t found = s.find_last_of("/");
    if (found != string::npos) {
        directory = s.substr(0, found + 1);
        fname = s.substr(found + 1);
    }

    d = opendir(directory.c_str());
    if (!d) {
        return false;
    } else {
        int len = fname.length();
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) {
                // cout << dir->d_name << endl;
                if (len == strlen(dir->d_name)) {
                    bool match = true;
                    for (int i = 0; i < len; i++) {
                        if (fname[i] != dir->d_name[i] && !(fname[i] == '#' &&
                                    isdigit(dir->d_name[i])))
                            match = false;
                    }
                    if (match) {
                        string c = directory + dir->d_name;
                        images.push_back(c);
                    }
                }
            }
        }
        closedir(d);
    }

    bool ret = true;

    for (int image_index = 0; image_index < images.size(); image_index++) {
        string curr = images[image_index];
        in_img_ = ImageHandler::LoadImage(curr);
        if (in_img_ == nullptr) {
            ret = false;
            continue;
        } else {
            int w = in_img_->width();
            int h = in_img_->height();
            out_img_ = new PixelBuffer(w, h,
                    in_img_->background_color());
        }
        // cout << "directory = " << directory << endl;
        // cout << "fname = " << fname << endl;

        string modified_out = output_file_;
        // Find the modified output file name if there are #'s in it
        if (fname.find("###") != string::npos) {
            string before = fname.substr(0, fname.find("###"));
            before = curr.substr(0, curr.find(before)) + before;
            string numbers = curr.substr(before.length(), 3);
            before = output_file_.substr(0, output_file_.find("###"));
            modified_out = before + numbers + output_file_.substr(
                           before.length() + 3);
        }
        // cout << "modified = " << modified_out << endl;

        // Process commands one at a time in order of appearance
        int commands_size = commands_.size();
        for (int i = 0; i < commands_size; i++) {
            bool swap = true;
            switch (commands_[i]) {
                case HELP:
                    PrintHelp();
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
                    delete out_img_;
                    out_img_ = imgtools::LoadImage(modified_out);
                    if (out_img_ == nullptr) {
                        ret = false;
                        delete in_img_;
                        break;
                    }
                    cout << imgtools::CompareImages(in_img_, out_img_) << endl;
                    break;
                default:
                    swap = false;
                    if (debug)
                        cout << "unrecognized switch case" << endl;
            }
            if (!ret)
                break;

            if (swap) {
                PixelBuffer* tmp = in_img_;
                in_img_ = out_img_;
                out_img_ = tmp;
            }
        }
        // Output the image created
        if (!imgtools::SaveImage(modified_out, in_img_))
            ret = false;

        delete in_img_;
        delete out_img_;
    }

    return ret;
}

bool CmdLineHandler::ProcessArguments() {
    if (!ParseArguments()) {
        if (debug)
            cout << "parsing args failed" << endl;
        PrintHelp();
        return false;
    }
    if (!RunCommands()) {
        if (debug)
            cout << "running commands failed" << endl;
        PrintHelp();
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
