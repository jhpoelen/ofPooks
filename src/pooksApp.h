#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"

#include "ofxMidi.h"
#include "editable.h"
#include "layer.h"
#include "layout.h"
#include "sample.h"
#include "sampleFactory.h"
#include "keyboardController.h"
#include "colorChannel.h"

const int MAX_SCREENS = 6;
const int MAX_LAYERS = 4;
const int MAX_LAYOUTS = 8;

class pooksApp : public ofBaseApp, public ofxMidiListener {
    
private:
    void loadColors();
    void loadLayouts();
    void handleCmdKey(int key);
    int keysToIndex[26];

    
public:
    virtual ~pooksApp();
    void setup();
    void update();
    void draw();
    void exit();
    
    void stepAlpha(int step);
    
    void selectSampleIndex(int newSampleIndex);
	void selectColorChannelIndex(int colorChannelIndex);
    
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
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
	
    ofTrueTypeFont ttf;
    ofTrueTypeFont ttf2;
    
    ofPoint listOfScreenCorners[MAX_SCREENS][4];
    
    Editable screenSettings[MAX_SCREENS];
    Layer screenLayerSettings[MAX_SCREENS][MAX_LAYERS];
    
    vector<Sample*> samples;
    vector <ColorChannel*> colorChannels;
    vector <Layout*> layouts;
        
    ofBuffer fileBuffer;
    
    int whichCorner;
	
    GLfloat homographyMatrix[16];
    
    int port;
    int id;
    int value;
    int value2;
    double timestamp;
    char msg[255];
    
    float masterAlpha;
    float masterVolume;
    float masterRate;
	

	
    // midi addon
    ofxMidiIn	midiIn;
		
    int selectedScreen;
    bool showWarpTool;
	
    ofPoint mousePos;
    
    KeyboardController keyboardController;
};

