#pragma once

#include "colorChannel.h"

#define ALPHABET_SIZE 26

class ColorChannelAlphabet : public ColorChannel {
  
public:
    virtual ofColor nextColor();
    virtual void loadColors();
    virtual ofColor selectColor(int colorIndex);
    
    
private:
    ofColor colors[ALPHABET_SIZE];
    int counter;
};