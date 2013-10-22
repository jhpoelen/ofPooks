#pragma once

#include "layout.h"

class LayoutGridVerticalNoisy : public Layout {
    
public:
    virtual void render(ofTexture texture, ColorChannel* colorChannel, Layer layer);
};