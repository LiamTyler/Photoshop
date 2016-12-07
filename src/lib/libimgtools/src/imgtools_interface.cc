/*******************************************************************************
 * Name            : filter_controller.cc
 * Project         : FlashPhoto
 * Module          : filter_controller
 * Description     : CC for FilterController
 * Copyright       : Group Bits Please
 * Creation Date   : 12/6/2016
 * Original Author : Liam Tyler
 *
 ******************************************************************************/

#include "lib/libimgtools/src/include/imgtools_interface.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/blur_filter.h"
#include "lib/libimgtools/src/include/edge_detect_filter.h"
#include "lib/libimgtools/src/include/sharpen_filter.h"
#include "lib/libimgtools/src/include/motion_blur_filter.h"
#include "lib/libimgtools/src/include/quantize_filter.h"
#include "lib/libimgtools/src/include/threshold_filter.h"
#include "lib/libimgtools/src/include/channels_filter.h"
#include "lib/libimgtools/src/include/emboss_filter.h"
#include "lib/libimgtools/src/include/saturation_filter.h"
#include "lib/libimgtools/src/include/image_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace imgtools {

void ApplyChannel(PixelBuffer* oldimage, PixelBuffer* newimage,
                  float red, float green, float blue) {
    ChannelsFilter c(red, green, blue);
    c.ApplyFilter(oldimage, newimage);
}

void ApplySaturate(PixelBuffer* oldimage, PixelBuffer* newimage, float amt) {
    SaturationFilter sat(amt);
    sat.ApplyFilter(oldimage, newimage);
}

void ApplyBlur(PixelBuffer* oldimage, PixelBuffer* newimage, float amt) {
    BlurFilter b(static_cast<int>(amt));
    b.ApplyFilter(oldimage, newimage);
}

void ApplySharpen(PixelBuffer* oldimage, PixelBuffer* newimage, float amt) {
    SharpenFilter s(amt);
    s.ApplyFilter(oldimage, newimage);
}

void ApplyMotionBlur(PixelBuffer* oldimage, PixelBuffer* newimage,
                     int amt, int direction) {
    MotionBlurFilter m(amt, direction);
    m.ApplyFilter(oldimage, newimage);
}

void ApplyEdgeDetect(PixelBuffer* oldimage, PixelBuffer* newimage) {
    EdgeDetectFilter e;
    e.ApplyFilter(oldimage, newimage);
}

void ApplyQuantize(PixelBuffer* oldimage, PixelBuffer* newimage, int bins) {
    QuantizeFilter q(bins);
    q.ApplyFilter(oldimage, newimage);
}
void ApplyThreshold(PixelBuffer* oldimage, PixelBuffer* newimage, float level) {
    ThresholdFilter t(level);
    t.ApplyFilter(oldimage, newimage);
}
void ApplySpecial(PixelBuffer* oldimage, PixelBuffer* newimage) {
    EmbossFilter emb;
    emb.ApplyFilter(oldimage, newimage);
}

PixelBuffer* LoadImage(const std::string& file_name) {
    return ImageHandler::LoadImage(file_name);
}

bool SaveImage(const std::string& file_name, const PixelBuffer* bufferToSave) {
    return ImageHandler::SaveImage(file_name, bufferToSave);
}

int CompareImages(const PixelBuffer* img1, const PixelBuffer* img2) {
    int img1_w = img1->width();
    int img1_h = img1->height();
    int img2_h = img2->height();
    int img2_w = img2->width();

    if (img1_w != img2_w || img1_h != img2_h)
        return 0;
    for (int r = 0; r < img1_h; r++) {
        for (int c = 0; c < img1_w; c++) {
            if (img1->get_pixel(c, r) != img2->get_pixel(c, r))
                return 0;
        }
    }

    return 1;
}

}  /* namespace imgtools */
