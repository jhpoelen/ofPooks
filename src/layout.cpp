#include "layout.h"


Layout::Layout() {
    shader.setup(320,240);
    frame = 0;
}

void Layout::update() {
    frame++;
}