/******************************************************************************
 * Name            : tool_factory.cc
 * Project         : BrushWork
 * Module          : Tool
 * Description     : Implementation of factory design pattern for tools
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 * 
 ******************************************************************************/

#include "lib/libimgtools/src/include/tool_factory.h"
#include "lib/libimgtools/src/include/tool.h"
#include "lib/libimgtools/src/include/pen.h"
#include "lib/libimgtools/src/include/eraser.h"
#include "lib/libimgtools/src/include/calligraphy.h"
#include "lib/libimgtools/src/include/highlighter.h"
#include "lib/libimgtools/src/include/spray_can.h"
#include "lib/libimgtools/src/include/rainbow.h"
#include "lib/libimgtools/src/include/blur_tool.h"
#include "lib/libimgtools/src/include/stamp_tool.h"

namespace image_tools {

    Tool* ToolFactory::CreateTool(int tool_id) {
        Tool* tool = nullptr;

        switch (tool_id) {
            case TOOL_PEN:
                tool = new TPen();
                break;
            case TOOL_ERASER:
                tool = new TEraser();
                break;
            case TOOL_SPRAYCAN:
                tool = new TSprayCan();
                break;
            case TOOL_CALLIGRAPHYPEN:
                tool = new TCalligraphy();
                break;
            case TOOL_HIGHLIGHTER:
                tool = new THighlighter();
                break;
            case TOOL_RAINBOW:
                tool = new TRainbow();
                break;
            case TOOL_BLUR:
                tool = new TBlur();
                break;
            case TOOL_STAMP:
                tool = new TStamp();
                break;
            default:
                tool = nullptr;
                break;
        }

        return tool;
    }

}  /* namespace image_tools */
