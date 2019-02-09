#include "sampleText.h"

bool SampleText::loadMovie(string name) {
    buffer = ofBufferFromFile(name);
    return font.load("frabk.ttf", 80);
};

bool SampleText::isLoaded() {
    return font.isLoaded();
};

void SampleText::update() {
    font.drawString(buffer.getText(), ofGetWidth()/3.0f, ofGetHeight()/2.0f);
};
