#include "colorChannelAlphabet.h"

class ColorChannelPoem : public ColorChannelAlphabet {
  
public:
    ColorChannelPoem(string textfilename);
    virtual ofColor nextColor();
    virtual ofColor selectColor(int colorIndex);
    
private:
    int position;
    int numberOfCharacters;
    vector<ofColor> poeticColorSequence;
    ofColor whitespace;
    ofColor newline;
    ofColor newstanza;
};
