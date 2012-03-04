/*
 *  ofxBlurShader.cpp
 *
 *  Created by Rick Companje on 25-10-10.
 *  updated on 15-07-11 for of007
 *  Based on the blurShader example by Theo
 *
 */

#include "smoothEdgeShader.h"

SmoothShader::SmoothShader() {
    enabled = false;
    initialized = false;
	alpha = 1.0;
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
	uniform float alpha;\
	uniform float width;\
	uniform float height;\
	uniform float red;\
	uniform float green;\
	uniform float blue;\
	\
	void main()\
	{\
		vec2 st = gl_TexCoord[0].st;\
		vec2 st_norm = st / vec2(width, height);\
		float edgeAlpha = 40.0 * (st_norm.s * st_norm.t * (1.0 - st_norm.s) * (1.0 - st_norm.t));\
		\
		vec4 color = texture2DRect(src_tex_unit0, st);\
		float lum = dot(lumCoeff, color);\
		if (red > 0.0 || green > 0.0 || blue > 0.0) {\
			color = vec4(lum,lum,lum,color[3]) * vec4(red/255.0, green/255.0, blue/255.0, 1.0);\
		}\
		gl_FragColor = color * vec4(1.0, 1.0, 1.0, alpha * edgeAlpha);\
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

void SmoothShader::begin(float width, float height) {
    if (!initialized) ofLog(OF_LOG_ERROR, "ofxBlurShader::setup(w,h) needs to be called first");
    if (!enabled) return;
        
	alphaShader.begin();
	alphaShader.setUniform1f("alpha", alpha);
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

