#pragma once

#include "colorChannel.h"
#include "layer.h"
#include "smoothShader.h"
#include "ofMain.h"


class Layout {
  
public:
    Layout();
    virtual void render(ofTexture texture, ColorChannel* colorChannel, Layer layer) = 0;
    virtual void update(Layer layer);
    
protected:
    SmoothShader shader;
    int frame = 0;
    int layoutFrame = 0;
    
};