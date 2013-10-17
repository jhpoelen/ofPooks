#pragma once

#include "ofMain.h"
const int MAX_COLORS = 8;


class ColorChannel {
  
public:
    virtual ofColor nextColor();
    virtual void loadColors();
    virtual ofColor selectColor(int colorIndex);
    
private:
    ofColor colors[MAX_COLORS];
};