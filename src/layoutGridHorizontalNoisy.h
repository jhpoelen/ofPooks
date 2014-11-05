#pragma once

#include "layout.h"

class LayoutGridHorizontalNoisy : public Layout {

public:
    LayoutGridHorizontalNoisy();
    virtual void render(ofTexture texture, ColorChannel *colorChannel, Layer layer);
    
private:
    int offset;
    
};

