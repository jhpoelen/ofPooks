#include "colorChannelAlphabet.h"



void ColorChannelAlphabet::loadColors() {
    unsigned char colorAlphabet[] = {
        'a',240,163,255,
        'b',0,177,220,
        'c',153,63,0,
        'd',76,0,92,
        'e',25,25,25,
        'f',0,92,49,
        'g',43,206,72,
        'h',255,204,153,
        'i',128,128,128,
        'j',148,255,181,
        'k',143,124,0,
        'l',157,204,0,
        'm',194,0,136,
        'n',0,51,128,
        'o',255,164,5,
        'p',255,168,187,
        'q',66,102,0,
        'r',255,0,16,
        's',94,241,242,
        't',0,153,143,
        'u',224,255,102,
        'v',116,10,255,
        'w',153,0,0,
        'x',255,255,128,
        'y',255,255,0,
        'z',255,80,5};

    for (int i=0; i < ALPHABET_SIZE; i++) {
        int red = colorAlphabet[i*4+1];
        int green = colorAlphabet[i*4+2];
        int blue = colorAlphabet[i*4+3];
        colors[i].set(red, green, blue);
    }
    counter = 0;
    
}

ofColor ColorChannelAlphabet::nextColor() {
    return selectColor(++counter);
}

ofColor ColorChannelAlphabet::selectColor(int colorIndex) {
    return colors[colorIndex % ALPHABET_SIZE];
}