#pragma once

#include "layout.h"

class LayoutNoisy : public Layout {
    
public:
    virtual void render(ofTexture texture, ColorChannel* colorChannel, Layer layer);
    virtual void update();
    
};