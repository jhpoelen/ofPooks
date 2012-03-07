/*
 *  twinklingStar.cpp
 *  ofPooks
 *
 *  Created by jorrit on 3/7/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "twinklingStar.h"

TwinklingStar::TwinklingStar() {
	newStar();
}
	
void TwinklingStar::update() {	
	timeInTicks += fadeRate;
	
	if (timeInTicks > MAX_FADE_STEPS * 2) {
		newStar();
	} else {
		alpha = (float)timeInTicks / MAX_FADE_STEPS;
		if (timeInTicks > MAX_FADE_STEPS) {
			alpha = 2.0 - alpha;
		} 
 		//position.x += speed.x;
		//position.y += speed.y;
	}
}

void TwinklingStar::newStar() {
	position.x = ofRandom(ofGetWidth());
	position.y = ofRandom(ofGetHeight());
	speed.x = ofRandom(-4.0, 4.0);
	speed.y = ofRandom(-4.0, 4.0);
	float randomSize = ofRandom(1.0, 3.0);
	size.x = (float)ofGetWidth()/randomSize;
	size.y = (float)ofGetWidth()/randomSize;
	fadeRate = (int)ofRandom(200.0, 300.0);	
	timeInTicks = 0;
	alpha = 0.0;
}