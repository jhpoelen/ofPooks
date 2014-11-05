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
#ifdef TARGET_OPENGLES
  STRINGIFY(
    attribute vec4 position;
    attribute vec4 color;
    attribute vec4 normal;
    attribute vec2 texcoord;

    uniform mat4 modelViewMatrix;
    uniform mat4 projectionMatrix;

    varying vec4 colorVarying;
    varying vec2 texCoordVarying;


    void main() {
      vec4 pos = projectionMatrix * modelViewMatrix * position;
      gl_Position = pos;
                            
      colorVarying = color;
      texCoordVarying = texcoord;
    }
  );
#else
  "void main() {\
		gl_TexCoord[0] = gl_MultiTexCoord0;\
		gl_Position = ftransform();\
	}";
#endif
	
	string smoothEdgeShader =
  #ifdef TARGET_OPENGLES
  STRINGIFY(
    precision highp float;

    uniform sampler2D src_tex_unit0;
    uniform float useTexture;
    uniform float useColors;
    uniform vec4 color;

    varying float depth;
    varying vec4 colorVarying;
    varying vec2 texCoordVarying;
        
    void main(){
      vec4 c;
      if(useColors>0.5){
        c = colorVarying;
      } else {
        c = color;
      }
      if (useTexture >0.5 ) {
        gl_FragColor = texture2D(src_tex_unit0, texCoordVarying)*c;
      } else {
        gl_FragColor = c;
      }
    }
  );
  #else
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
  #endif
    
    if (alphaShader.setupShaderFromSource(GL_FRAGMENT_SHADER, smoothEdgeShader)) {
		ofLog(OF_LOG_NOTICE, "created fragment shader");
    initialized = true;
	} else {
		ofLog(OF_LOG_ERROR, "failed to create fragment shader");
	}
  if (alphaShader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShader)) {
    ofLog(OF_LOG_NOTICE, "created vertex shader");
  } else {
    ofLog(OF_LOG_ERROR, "failed to create vertex shader");
    initialized = false;
  }

  alphaShader.linkProgram();
  enabled = true;
}

void SmoothShader::begin(float width, float height, float screenAlpha, float layerAlpha, float contrast, float luminance, float red, float green, float blue) {
    if (initialized && enabled) {
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
}

void SmoothShader::end() {
    if (initialized && enabled) {
        alphaShader.end();
    }
}

