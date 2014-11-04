#pragma once

#include "colorChannelAlphabet.h"

class ColorChannelPoem : public ColorChannelAlphabet {
  
public:
    ColorChannelPoem(string textfilename);
    virtual ofColor nextColor();
    virtual ofColor selectColor(int colorIndex);
    
protected:
    vector<ofColor> poeticColorSequence;
    ofColor newline;
    
private:
    int position;
    int numberOfCharacters;
    ofColor whitespace;

    ofColor newstanza;
};
