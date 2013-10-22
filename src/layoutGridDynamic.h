#pragma once

#include "layoutGrid.h"

class LayoutGridDynamic : public LayoutGrid {
    
public:
    virtual int selectColorIndex(int row, int col, int nrows);

};