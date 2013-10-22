#include "layoutGridDynamic.h"

int LayoutGridDynamic::selectColorIndex(int row, int col, int nrows) {
    return nrows * col + row + layoutFrame;
}