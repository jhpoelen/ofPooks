#pragma once

#include "colorChannel.h"
#include "layer.h"
#include "smoothShader.h"
#include "ofMain.h"


class Layout {
  
public:
    Layout();
    virtual void render(ofTexture texture, ColorChannel* colorChannel, Layer layer) = 0;
    virtual void update() = 0;
    
protected:
    SmoothShader shader;
    
};