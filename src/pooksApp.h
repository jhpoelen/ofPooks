#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxMidi.h"
#include "smoothShader.h"
#include "editable.h"
#include "layer.h"
#include "twinklingStar.h"
#include "sample.h"

const int MAX_COLORS = 8;
const int MAX_SCREENS = 6;
const int MAX_LAYERS = 4;
const int MAX_LAYOUTS = 2;
const int MAX_STARS = 24;

class pooksApp : public ofBaseApp, public ofxMidiListener {

	public:
        virtual ~pooksApp();
		void setup();
		void update();
		void draw();
		void exit();
		
		void loadSamples();
    
        void selectSampleIndex(int newSampleIndex);
	
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
		
		vector<Sample*> samples;
    
		TwinklingStar stars[MAX_STARS];
    
        ofBuffer fileBuffer;
		
		int whichCorner;
	
		GLfloat homographyMatrix[16]; 
		
		// vars
		int port;
		int id;
		int value;
		int value2;
		double timestamp;
		char msg[255];
    
        float masterAlpha;
        float masterVolume;
	
		ofColor colors[MAX_COLORS];
	
		// midi addon
		ofxMidiIn	midiIn;
	
		SmoothShader shader;
	
		int selectedScreen;
		bool showWarpTool;
	
		ofPoint mousePos;
};

