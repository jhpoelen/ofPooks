#include "layout.h"


Layout::Layout() {
    shader.setup(320,240);
}

void Layout::update(Layer layer) {
    frame++;
    if (layer.layoutSpeed > 0 && frame % ((int)(1 + 10/ (1 + layer.layoutSpeed * 10))) == 0) {
        layoutFrame++;
    }
}