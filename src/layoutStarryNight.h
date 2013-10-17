#pragma once

#include "layout.h"
#include "twinklingStar.h"

const int MAX_STARS = 24;

class LayoutStarryNight : public Layout {
  
public:
    virtual void render(ofTexture texture, ColorChannel *colorChannel, Layer layer);
    virtual void update();
    
private:
    TwinklingStar stars[MAX_STARS];
    
};