#include "layoutGrid.h"

void LayoutGrid::render(ofTexture texture, ColorChannel* colorChannel, Layer layer) {
    float complexity = layer.complexity;
    int nrows = (complexity * 64) + 1;
    int ncols = nrows;
    float fill = 0.85;
    int xSize = fill * ofGetWidth() / nrows;
    int xMargin = ofGetWidth() / nrows - xSize;
    int ySize = fill * ofGetHeight() / ncols;
    int yMargin = ofGetHeight() / ncols - ySize;
    for (int row=0; row<nrows; row++) {
        for (int col=0; col<ncols; col++) {
            ofColor selectedColor = colorChannel->selectColor(selectColorIndex(row, col, nrows));
            int lum = selectedColor.r + selectedColor.g + selectedColor.b;
            if (lum > 2) {
                shader.begin(texture.getWidth(),
                         texture.getHeight(),
                         layer.masterScreenAlpha,
                         layer.alpha,
                         layer.contrast,
                         layer.luminance,
                         selectedColor.r,
                         selectedColor.g,
                         selectedColor.b);
                int xOffset = row * xSize + xMargin * row + 0.5f * xMargin;
                int yOffset = col * ySize + yMargin * col + 0.5f * yMargin;
                texture.draw(xOffset, yOffset, xSize, ySize);
                shader.end();
            }
        }
    }
}

int LayoutGrid::selectColorIndex(int row, int col, int nrows) {
    return nrows * col + row;
}
