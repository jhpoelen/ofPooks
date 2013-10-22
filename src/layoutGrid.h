#pragma once

#include "layout.h"

class LayoutGrid : public Layout {
  
public:
    virtual void render(ofTexture texture, ColorChannel* colorChannel, Layer layer);
    virtual int selectColorIndex(int row, int col, int nrows);
};