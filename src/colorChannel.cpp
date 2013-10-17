#include "colorChannel.h"


void ColorChannel::loadColors() {
    // black
	colors[0].set(0, 0, 0);
	// royal yellow
	colors[1].set(250, 218, 94);
	// burnt orange
	colors[2].set(204, 85, 0);
	// yellow gold
	colors[3].set(255, 215, 0);
	// light sea green
	colors[4].set(230, 0, 0);
	// chinese red
	colors[5].set(230, 0, 0);
	// chinese red (subsidiary 1)
	colors[6].set(254, 40, 14);
	// chinese red (subsidiary 2)
	colors[7].set(242, 85, 0);
	// chinese red (subsidiary 3)
	colors[8].set(137, 0, 24);
}

ofColor ColorChannel::nextColor() {
    return colors[rand() % MAX_COLORS];
}

ofColor ColorChannel::selectColor(int colorIndex) {
    return colors[colorIndex % MAX_COLORS];
}
