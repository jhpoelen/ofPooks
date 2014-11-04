#include "colorChannelPoemNoRepetitions.h"


ColorChannelPoemNoRepetitions::ColorChannelPoemNoRepetitions(string filename) : ColorChannelPoem(filename) {
    
}

ofColor ColorChannelPoemNoRepetitions::selectColor(int colorIndex) {
    return  colorIndex < poeticColorSequence.size()
                        ? poeticColorSequence.at(colorIndex % poeticColorSequence.size())
                        : newline;
}

