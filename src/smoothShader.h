#pragma once 

#include "ofMain.h"

class SmoothShader {
public:
	
    SmoothShader(); 
    
	void setup(float w, float h);
	void begin(float width, float height, float screenAlpha, float layerAlpha);
	void end();
	void draw(float x=0, float y=0, float w=0, float h=0);
    
    bool enabled;
    
    ofShader alphaShader;
	
	float red;
	float green;
	float blue;
	
	
private:
    bool initialized;
};
