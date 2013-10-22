#include "layoutHorizontalStripes.h"

void LayoutHorizontalStripes::render(ofTexture texture, ColorChannel *colorChannel, Layer layer) {
    float complexity = layer.complexity;
    int nrows = 1;
    int ncols = (complexity * 128) + 1;
    int xSize = ofGetWidth() / nrows;
    int ySize = ofGetHeight() / ncols;
    for (int row=0; row<nrows; row++) {
        for (int col=0; col<ncols; col++) {
            ofColor selectedColor = colorChannel->selectColor(nrows * col + row + layoutFrame);
            shader.begin(texture.getWidth(),
                         texture.getHeight(),
                         layer.masterScreenAlpha,
                         layer.alpha,
                         layer.contrast,
                         layer.luminance,
                         selectedColor.r,
                         selectedColor.g,
                         selectedColor.b);
            int xOffset = row * xSize;
            int yOffset = col * ySize;
            texture.draw(xOffset, yOffset, xSize, ySize);
            shader.end();
        }
    }
}

void LayoutHorizontalStripes::update() {
    
}
