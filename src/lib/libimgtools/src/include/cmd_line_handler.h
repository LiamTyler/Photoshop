/*******************************************************************************
 * Name            : cmd_line_handler.h
 * Project         : libimgtools
 * Module          : CmdLineHandler
 * Description     : Handle commands done through the command line
 * Copyright       : Group Bits Please
 * Creation Date   : 12/6/16
 * Original Author : Liam Tyler
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CMD_LINE_HANDLER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CMD_LINE_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include "lib/libimgtools/src/include/pixel_buffer.h"

/**
 * @brief Class responsible for parsing the command line arguments and running
 * them
 *
 * The handlers works in two phases. First, parse all the commands, and check
 * for validity, correct number, and extensions. Then, run through the commands
 * given for each image applicable, and save if necessary.
 */
class CmdLineHandler {
 public:
  CmdLineHandler(int argc, char** argv);
  /**
   * @brief Both parse and run the commands
   *
   * @return False if any error occurred, True otherwise
   */
  bool ProcessArguments();

  /**
   * @brief Helper function to print the information (for debugging).
   */
  void PrintInfo();

  /**
   * @brief If anything is invalid or errors, print the help message.
   */
  void PrintHelp();
  enum Command {
    HELP,
    SHARPEN,
    EDGE,
    THRESHOLD,
    QUANTIZE,
    BLUR,
    SATURATE,
    CHANNEL,
    COMPARE,
    IMAGE,
    ARG
  };

 private:
  CmdLineHandler(const CmdLineHandler& c) = delete;
  CmdLineHandler& operator=(const CmdLineHandler& c) = delete;

  /**
   * @brief parses through the command line arguments and readies them
   * for running.
   *
   * @return False if any commands or arguments were invalid
   */
  bool ParseArguments();

  /**
   * @brief Actually run the commands provided
   *
   * @return True if no errors occurred, false otherwise.
   */
  bool RunCommands();

  /**
   * @brief validate the args provided for the command given
   */
  bool ValidateArgs(int index, Command command);
  Command get_index(const char* arg);
  bool is_number(const char* arg);
  int argc_;
  char** argv_;
  int current_arg_;
  float sharpen_amt_;
  float threshold_amt_;
  int quantize_amt_;
  float blur_amt_;
  float saturate_amt_;
  float channel_red_amt_;
  float channel_green_amt_;
  float channel_blue_amt_;
  std::string input_file_;
  std::string output_file_;
  image_tools::PixelBuffer* in_img_;
  image_tools::PixelBuffer* out_img_;
  std::vector<CmdLineHandler::Command> commands_;
};

#endif  /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CMD_LINE_HANDLER_H_ */
