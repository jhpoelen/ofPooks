#include "colorChannelPoem.h"


ColorChannelPoem::ColorChannelPoem(string textFilename) {
    loadColors();
    position = 0;
    whitespace.set(1,0,0);
    newline.set(1,0,0);
    newstanza.set(1,0,0);
    ofBuffer buffer = ofBufferFromFile(textFilename);
    ofLog(OF_LOG_NOTICE, "read [" + buffer.getText() + "] from [" + textFilename + "]");
    buffer.resetLineReader();
    while (!buffer.isLastLine()) {
        string line = buffer.getNextLine();
        for (int i=0; i<line.size(); i++) {
            unsigned char character = line.at(i) - 'A';
            if (character >= 26) {
                character = line.at(i) - 'a';
            }
            if (character < 26) {
                ofColor color = ColorChannelAlphabet::selectColor((int)character);
                poeticColorSequence.push_back(color);
            } else {
                poeticColorSequence.push_back(whitespace);
            }
        }
    }
}

ofColor ColorChannelPoem::nextColor() {
    position = position % poeticColorSequence.size();
    return poeticColorSequence.at(position++);
}

ofColor ColorChannelPoem::selectColor(int colorIndex) {
    return poeticColorSequence.at(colorIndex % poeticColorSequence.size());
}

