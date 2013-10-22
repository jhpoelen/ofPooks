#include "colorChannelPassthrough.h"

void ColorChannelPassthrough::loadColors() {
	color.set(0,0,0);
}

ofColor ColorChannelPassthrough::nextColor() {
    return color;
}

ofColor ColorChannelPassthrough::selectColor(int colorIndex) {
    return color;
}
