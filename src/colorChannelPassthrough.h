#pragma once

#include "colorChannel.h"

class ColorChannelPassthrough : public ColorChannel {
  
public:
    virtual ofColor nextColor();
    virtual void loadColors();
    virtual ofColor selectColor(int colorIndex);
    
private:
    ofColor color;

    
};