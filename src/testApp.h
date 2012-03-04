#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxMidi.h"
#include "ofxBlurShader.h"
#include "smoothEdgeShader.h"

//stupid ball class 
class ball{
	
public:
	ball(){
		
	}
	
	void setup(float x, float y, float r){
		pos.x = x;
		pos.y = y;
		pos.z = r;
		
		vel.x = 2.0;
		vel.y = 1.6;
	}	
	
	void update(int width, int height){
		if( pos.x + pos.z >= width){
			pos.x = width - pos.z;
			vel.x *= -1;
		}else if( pos.x - pos.z <= 0){
			pos.x = pos.z;
			vel.x *= -1;
		}
		
		if( pos.y + pos.z >= height){
			pos.y = height - pos.z;
			vel.y *= -1;
		}else if( pos.y - pos.z <= 0){
			pos.y = pos.z;
			vel.y *= -1;
		}
		
		pos.x += vel.x;
		pos.y += vel.y;
	}
	
	void draw(){	
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofCircle(pos.x, pos.y,  pos.z);
		ofSetRectMode(OF_RECTMODE_CORNER);			
	}
	
	ofPoint pos;
	ofPoint vel;
	
};

const int MAX_COLORS = 4;
const int MAX_SCREENS = 4;


class testApp : public ofBaseApp, public ofxMidiListener {

	public:
		void setup();
		void update();
		void draw();
		void exit();
		
		void renderWarpTool(int screenNumber);
		void renderScreen(ofPoint corners[]);
	
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
	
		ofImage img;
		ball balls[80];
	
		ofPoint listOfScreenCorners[MAX_SCREENS][4];
		int whichCorner;
	
		GLfloat homographyMatrix[16]; 
	
		ofVideoPlayer fingerMovie0;
		ofVideoPlayer fingerMovie1;
		ofVideoPlayer fingerMovie2;
	
		
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
	
		float alpha;
		float speed;
		SmoothShader blur;
	
		int selectedScreen;
		bool showWarpTool;
};

