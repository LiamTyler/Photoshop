
#ifndef PNGHANDLER_H
#define PNGHANDLER_H

using image_tools::PixelBuffer;

//class ColorData;
//class PixelBuffer;
class FlashPhoto;
class BaseGfxApp;

class PngHandler
{
public:
  PixelBuffer* read_PNG_file (char* name, PixelBuffer* buffer);
  void write_PNG_file (char* name, PixelBuffer* buffer);
};

#endif
