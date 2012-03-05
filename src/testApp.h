#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxMidi.h"
#include "smoothShader.h"
#include "editable.h"
#include "layer.h"

const int MAX_COLORS = 4;
const int MAX_SCREENS = 4;
const int MAX_LAYERS = 2;
const int MAX_LAYOUTS = 2;
const int MAX_SAMPLES = 2;

class testApp : public ofBaseApp, public ofxMidiListener {

	public:
		void setup();
		void update();
		void draw();
		void exit();
		
		void loadSamples();
	
		void renderWarpTool(int screenNumber);
		void renderScreen(int screenIndex);
		void warpScreen(int screenIndex);
	
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		void newMidiMessage(ofxMidiEventArgs& eventArgs);
	
		ofTrueTypeFont ttf;
		ofTrueTypeFont ttf2;
		
		ofPoint listOfScreenCorners[MAX_SCREENS][4];
		
		Editable screenSettings[MAX_SCREENS];
		Layer screenLayerSettings[MAX_SCREENS][MAX_LAYERS];		
		Editable screenLayerLayoutSettings[MAX_SCREENS][MAX_LAYERS][MAX_LAYOUTS];
		
		ofVideoPlayer samples[MAX_SAMPLES];
		
		int whichCorner;
	
		GLfloat homographyMatrix[16]; 
		
		// vars
		int port;
		int id;
		int value;
		int value2;
		double timestamp;
		char msg[255];
	
		ofColor colors[MAX_COLORS];
	
		// midi addon
		ofxMidiIn	midiIn;
	
		float speed;
		SmoothShader shader;
	
		int selectedScreen;
		bool showWarpTool;
	
		ofPoint mousePos;
};

