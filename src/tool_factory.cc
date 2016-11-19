/*******************************************************************************
 * Name            : tool_factory.cc
 * Project         : BrushWork
 * Module          : Tool
 * Description     : Implementation of factory design pattern for tools
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 * 
 *******************************************************************************/

/*******************************************************************************
 *  * Includes
 *   ******************************************************************************/
#include "include/tool_factory.h"
#include "include/tool.h"
#include "include/pen.h"
#include "include/eraser.h"
#include "include/calligraphy.h"
#include "include/highlighter.h"
#include "include/spray_can.h"
#include "include/rainbow.h"
#include "include/blur_tool.h"

/*******************************************************************************
 *  * Namespaces
 *   ******************************************************************************/
namespace image_tools {

    /*******************************************************************************
     *  * Member Functions
     *   ******************************************************************************/
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
            default:
                tool = nullptr;
                break;
        }

        return tool;
    }

}  /* namespace image_tools */
