/*
 *  layer.h
 *  ofPooks
 *
 *  Created by jorrit on 3/4/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "editable.h"

class Layer: public Editable {

public:
	int selectedLayoutIndex;
	int selectedSampleIndex;
	int selectedColorIndex;
	float alpha;
	float speed;
	float contrast;
	float luminance;
	float complexity;
	
	Layer() : Editable() {
		selectedColorIndex = 0;
		selectedSampleIndex = 0;
		selectedLayoutIndex = 0;
		alpha = 0.0;
		speed = 1.0;
	}
};
