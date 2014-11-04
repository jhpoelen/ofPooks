#pragma once

#include "colorChannelPoem.h"

class ColorChannelPoemNoRepetitions : public ColorChannelPoem {
    
public:
    ColorChannelPoemNoRepetitions(string filename);
    virtual ofColor selectColor(int colorIndex);
        
    
};