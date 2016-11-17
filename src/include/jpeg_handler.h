#ifndef JPEGHANDLER_H
#define JPEGHANDLER_H

class ColorData;
class PixelBuffer;
class FlashPhoto;
class BaseGfxApp;

class JpegHandler
{
public:
  PixelBuffer* read_JPEG_file (char* name, PixelBuffer* buffer);
  void write_JPEG_file (char* name, PixelBuffer* buffer);
};

#endif
