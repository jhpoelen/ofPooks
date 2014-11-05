#pragma once 

#include "ofMain.h"

class SmoothShader {
public:
	
    SmoothShader(); 
    
	void setup(float w, float h);
	void begin(float width, 
				float height, 
				float screenAlpha, 
				float layerAlpha, 
				float contrast, 
				float luminance, 
				float red, 
				float green, 
				float blue);
	void end();
	void draw(float x=0, float y=0, float w=0, float h=0);
    
    bool enabled;
    
    ofShader alphaShader;
	
private:
    void setupOpenGL_ES(float w, float h);
    void setupNonOpenGL_ES(float w, float h);

    bool initialized;
};
