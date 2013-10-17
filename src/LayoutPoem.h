#pragma once

#include "layout.h"

class LayoutPoem : public Layout {
  
public:
    LayoutPoem(string filename);
    virtual void render(ofTexture texture, ColorChannel* colorChannel, Layer layer);
    virtual void update();

private:
    ofBuffer buffer;
    int numberOfLines;

    
};