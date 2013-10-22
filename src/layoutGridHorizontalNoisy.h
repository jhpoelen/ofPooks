#pragma once

#include "layout.h"

class LayoutGridHorizontalNoisy : public Layout {

public:
    virtual void render(ofTexture texture, ColorChannel *colorChannel, Layer layer);
    
private:
    int offset = 0;
    
};

