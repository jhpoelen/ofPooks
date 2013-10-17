#pragma once

#include "editable.h"

class Layer: public Editable {

public:
	int selectedLayoutIndex;
	int selectedSampleIndex;
	int selectedColorIndex;
    float masterScreenAlpha;
	float alpha;
	float speed;
	float contrast;
	float luminance;
	float complexity;
	
	Layer() : Editable() {
		selectedColorIndex = 0;
		selectedSampleIndex = 0;
		selectedLayoutIndex = 0;
        masterScreenAlpha = 0.0;
		alpha = 0.0;
		speed = 1.0;
	}
};
