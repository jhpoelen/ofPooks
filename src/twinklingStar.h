/*
 *  twinklingStar.h
 *  ofPooks
 *
 *  Created by jorrit on 3/7/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once;

#include "ofMain.h"

const int MAX_FADE_STEPS = 10000;

class TwinklingStar {
	
public:
	float alpha;
	ofPoint position;
	ofPoint speed;
	ofPoint size;	
	int fadeRate;
	int timeInTicks;
	
	void update();
	void newStar();
	TwinklingStar();
	
};


