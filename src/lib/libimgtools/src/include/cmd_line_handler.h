#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CMD_LINE_HANDLER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CMD_LINE_HANDLER_H_

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

#include <string>
#include <vector>
#include "lib/libimgtools/src/include/pixel_buffer.h"

class CmdLineHandler {
 public:
  CmdLineHandler();
  void ParseArguments(int argc, char* argv[]);
  void RunCommands();
 private:
  CmdLineHandler(const CmdLineHandler& c) = delete;
  CmdLineHandler& operator=(const CmdLineHandler& c) = delete;
  std::string input_file_;
  std::string output_file_;
  image_tools::PixelBuffer* in_img_;
  image_tools::PixelBuffer* scratch_img_;
  std::vector<std::string> commands_;
};

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CMD_LINE_HANDLER_H_
