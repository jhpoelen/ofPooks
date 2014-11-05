#include "layoutGridHorizontalNoisy.h"

LayoutGridHorizontalNoisy::LayoutGridHorizontalNoisy() {
  offset = 1;
}

void LayoutGridHorizontalNoisy::render(ofTexture texture, ColorChannel *colorChannel, Layer layer) {
    float complexity = layer.complexity;
    float noiseFactor = ofGetHeight()/(1 + complexity * 12);
    long int n = getpid();
    ofSeedRandom(n);
    int x = -noiseFactor/2 + ofRandom(noiseFactor);
    int y = -noiseFactor/2 + ofRandom(noiseFactor);
    int xSize = ofGetWidth() / (30 + ((complexity * 64) + 1));
    int ySize = ofGetHeight() / ((complexity * 64) + 1);
    int count = layoutFrame;
    while (y < ofGetHeight()) {
        int ySizeNew = ySize - noiseFactor/2 + ofRandom(noiseFactor);
        while (x < ofGetWidth()) {
            int xSizeNew = xSize - noiseFactor/2 + ofRandom(noiseFactor);
            if (rand() % 10 != 0) {
                ofColor selectedColor = colorChannel->selectColor(count);
                shader.begin(texture.getWidth(),
                             texture.getHeight(),
                             layer.masterScreenAlpha,
                             layer.alpha,
                             layer.contrast,
                             layer.luminance,
                             selectedColor.r,
                             selectedColor.g,
                             selectedColor.b);
                texture.draw(x, y, xSizeNew, ySizeNew);
                shader.end();
                count++;
            }
            x += xSizeNew;
        }
        x = -noiseFactor/2 + ofRandom(noiseFactor);
        y += ySizeNew;
    }
}
