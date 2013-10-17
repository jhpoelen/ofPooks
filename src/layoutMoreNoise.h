#pragma once

#include "layout.h"

class LayoutMoreNoise : public Layout {

public:
    virtual void render(ofTexture texture, ColorChannel *colorChannel, Layer layer);
    virtual void update();
    
};

