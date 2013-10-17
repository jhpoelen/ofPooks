#include "LayoutPoem.h"

LayoutPoem::LayoutPoem(string filename) : Layout() {
    buffer = ofBufferFromFile(filename);
    ofLog(OF_LOG_NOTICE, "read [" + buffer.getText() + "] from [" + filename + "]");
    numberOfLines = 0;
    buffer.getFirstLine();
    while (!buffer.isLastLine()) {
        buffer.getNextLine();
        numberOfLines++;
    }
    numberOfLines = numberOfLines == 0 ? 1 : numberOfLines;
}

void LayoutPoem::render(ofTexture texture, ColorChannel* colorChannel, Layer layer) {
    int nItems = layer.complexity * 64 + 1;
    int xSize = ofGetWidth() / nItems;
    for(int lineNumber = 0; lineNumber < nItems; lineNumber++) {
        string line = buffer.isLastLine() ? buffer.getFirstLine() : buffer.getNextLine();
        for (int letterInLine=0; letterInLine<line.size(); letterInLine++) {
            unsigned char character = line.at(letterInLine) - 'A';
            if (character >= 26) {
                character = line.at(letterInLine) - 'a';
            }
            if (character < 26) {
                ofColor selectedColor = colorChannel->selectColor(character);
                shader.begin(texture.getWidth(),
                         texture.getHeight(),
                         layer.masterScreenAlpha,
                         layer.alpha,
                         layer.contrast,
                         layer.luminance,
                         selectedColor.r,
                         selectedColor.g,
                         selectedColor.b);
                int xOffset = letterInLine * xSize;
                int yOffset = lineNumber * xSize;
                texture.draw(xOffset, yOffset, xSize, xSize);
                shader.end();
            }
        }
    }
}

void LayoutPoem::update() {
    
}