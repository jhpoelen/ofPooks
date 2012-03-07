/*
 *  ofxBlurShader.cpp
 *
 *  Created by Rick Companje on 25-10-10.
 *  updated on 15-07-11 for of007
 *  Based on the blurShader example by Theo
 *
 */

#include "smoothShader.h"

SmoothShader::SmoothShader() {
    enabled = false;
    initialized = false;
}

void SmoothShader::setup(float w, float h) {
	
	string vertexShader =
	"void main() {\
		gl_TexCoord[0] = gl_MultiTexCoord0;\
		gl_Position = ftransform();\
	}";
	
	string smoothEdgeShader =
	"const vec4 lumCoeff = vec4(0.2125, 0.7154, 0.0721, 0.0);\
	uniform sampler2DRect src_tex_unit0;\
	uniform float layerAlpha;\
	uniform float screenAlpha;\
	uniform float width;\
	uniform float height;\
	uniform float red;\
	uniform float green;\
	uniform float blue;\
	uniform float contrast;\
	uniform float luminance;\
	\
	void main()\
	{\
		vec2 st = gl_TexCoord[0].st;\
		vec2 st_norm = st / vec2(width, height);\
		float edgeAlpha = 80.0 * (st_norm.s * st_norm.t * (1.0 - st_norm.s) * (1.0 - st_norm.t));\
		vec4 color = texture2DRect(src_tex_unit0, st);\
		float lum =  dot(lumCoeff, color);\
		if (red > 0.0 || green > 0.0 || blue > 0.0) {\
			lum = 10.0 * luminance * smoothstep(0.75, 1.0, 1.0-lum);\
			color = lum * vec4(red/255.0, green/255.0, blue/255.0, 1.0);\
		}\
		gl_FragColor = color * vec4(1.0, 1.0, 1.0, layerAlpha * edgeAlpha * screenAlpha);\
	}";
    
    if (alphaShader.setupShaderFromSource(GL_FRAGMENT_SHADER, smoothEdgeShader)) {
		ofLog(OF_LOG_NOTICE, "created shader");
	} else {
		ofLog(OF_LOG_NOTICE, "failed to create shader");
	}
    alphaShader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
    alphaShader.linkProgram();
    
    initialized = true;
    enabled = true;
}

void SmoothShader::begin(float width, float height, float screenAlpha, float layerAlpha, float contrast, float luminance, float red, float green, float blue) {
    if (!initialized) ofLog(OF_LOG_ERROR, "ofxBlurShader::setup(w,h) needs to be called first");
    if (!enabled) return;
        
	alphaShader.begin();
	alphaShader.setUniform1f("layerAlpha", layerAlpha);
	alphaShader.setUniform1f("screenAlpha", screenAlpha);

	alphaShader.setUniform1f("contrast", contrast);
	alphaShader.setUniform1f("luminance", luminance);
	
	alphaShader.setUniform1f("width", width);
	alphaShader.setUniform1f("height", height);
	
	alphaShader.setUniform1f("red", red);
	alphaShader.setUniform1f("green", green);
	alphaShader.setUniform1f("blue", blue);
}

void SmoothShader::end() {
    if (!enabled) return;

	alphaShader.end();
	
}

