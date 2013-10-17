#pragma once

#include "layout.h"

class LayoutVerticalStripes : public Layout {
    
public:
    virtual void render(ofTexture texture, ColorChannel* colorChannel, Layer layer);
    virtual void update();
    
};