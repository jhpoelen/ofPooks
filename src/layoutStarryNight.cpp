#include "layoutStarryNight.h"

void LayoutStarryNight::render(ofTexture texture, ColorChannel *colorChannel, Layer layer) {
    float complexity = layer.complexity;
    ofSetRectMode(OF_RECTMODE_CENTER);
    int count = layoutFrame;
    for (int k=0; k<MAX_STARS; k++) {
        TwinklingStar star = stars[k];
        ofColor selectedColor = colorChannel->selectColor(count);
        shader.begin(texture.getWidth(),
                     texture.getHeight(),
                     layer.masterScreenAlpha,
                     layer.alpha * star.alpha,
                     layer.contrast,
                     layer.luminance,
                     selectedColor.r,
                     selectedColor.g,
                     selectedColor.b);
        texture.draw(star.position.x, star.position.y, star.size.x * complexity * 10.0, star.size.y * complexity * 10.0);
        shader.end();
        count++;
    }
    ofSetRectMode(OF_RECTMODE_CORNER);
}

void LayoutStarryNight::update(Layer layer) {
    Layout::update(layer);
    for (int k=0; k<MAX_STARS; k++) {
        stars[k].update();
    }
}