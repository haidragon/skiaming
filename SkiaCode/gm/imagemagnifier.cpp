/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "gm.h"
#include "SkMagnifierImageFilter.h"

#define WIDTH 500
#define HEIGHT 500

namespace skiagm {

class ImageMagnifierGM : public GM {
public:
    ImageMagnifierGM() {
        this->setBGColor(0xFF000000);
    }

protected:
    virtual uint32_t onGetFlags() const SK_OVERRIDE {
        // Skip tiled drawing until https://code.google.com/p/skia/issues/detail?id=781 is fixed.
        return this->INHERITED::onGetFlags() | GM::kSkipTiled_Flag;
    }

    virtual SkString onShortName() SK_OVERRIDE {
        return SkString("imagemagnifier--62");
    }

    virtual SkISize onISize() SK_OVERRIDE {
        return make_isize(WIDTH, HEIGHT);
    }

    virtual void onDraw(SkCanvas* canvas) SK_OVERRIDE {
        SkPaint paint;
        paint.setImageFilter(
            new SkMagnifierImageFilter(
                SkRect::MakeXYWH(SkIntToScalar(125), SkIntToScalar(125),
                                 SkIntToScalar(WIDTH / 2),
                                 SkIntToScalar(HEIGHT / 2)),
                100))->unref();
        canvas->saveLayer(NULL, &paint);
        paint.setAntiAlias(true);
        const char* str = "The quick brown fox jumped over the lazy dog.";
        srand(1234);
        for (int i = 0; i < 25; ++i) {
            int x = rand() % WIDTH;
            int y = rand() % HEIGHT;
            paint.setColor(rand() % 0x1000000 | 0xFF000000);
            paint.setTextSize(SkIntToScalar(rand() % 300));
            canvas->drawText(str, strlen(str), SkIntToScalar(x),
                             SkIntToScalar(y), paint);
        }
        canvas->restore();
    }

private:
    typedef GM INHERITED;
};

//////////////////////////////////////////////////////////////////////////////

static GM* MyFactory(void*) { return new ImageMagnifierGM; }
static GMRegistry reg(MyFactory);

}
