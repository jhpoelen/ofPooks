#include "layoutTelevision.h"


void LayoutTelevision::render(ofTexture texture, ColorChannel* colorChannel, Layer layer) {
    ofColor selectedColor = colorChannel->nextColor();
    shader.begin(texture.getWidth(),
                 texture.getHeight(),
                 layer.masterScreenAlpha,
                 layer.alpha,
                 layer.contrast,
                 layer.luminance,
                 selectedColor.r,
                 selectedColor.g,
                 selectedColor.b);
    texture.draw(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
}

void LayoutTelevision::update() {
    
}