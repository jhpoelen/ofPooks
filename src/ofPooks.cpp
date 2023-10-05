#include "ofPooks.h"
#include <pwd.h>
#include <unistd.h>
#include "ofUtils.h"
#include "colorChannelAlphabet.h"
#include "colorChannelPoem.h"
#include "colorChannelPassthrough.h"
#include "colorChannelPoemNoRepetitions.h"
#include "layoutTelevision.h"
#include "layoutGrid.h"
#include "layoutGridDynamic.h"
#include "layoutHorizontalStripes.h"
#include "layoutVerticalStripes.h"
#include "layoutStarryNight.h"
#include "layoutGridVerticalNoisy.h"
#include "layoutGridHorizontalNoisy.h"

void ofPooks::setup() {
    // ensure to load from app bundle resources
    ofSetDataPathRoot("../Resources/");

    //loads load in some truetype fonts

    ttf.load("frabk.ttf", 80);
    ttf2.load("frabk.ttf", 14);

    masterAlpha = 1.0;
    masterVolume = 1.0;
    masterRate = 1.0;

    ofSetEscapeQuitsApp(false);

    loadColors();

    loadLayouts();

    selectedScreen = 0;
    showWarpTool = false;


    //we run at 60 fps!
    ofSetVerticalSync(true);

    //this is just for our gui / mouse handles
    //this will end up being the destination quad we are warping too
    for (int i=0; i<MAX_SCREENS; i++) {
        listOfScreenCorners[i][0].x = 0.0;
        listOfScreenCorners[i][0].y = 0.0;

        listOfScreenCorners[i][1].x = 1.0;
        listOfScreenCorners[i][1].y = 0.0;

        listOfScreenCorners[i][2].x = 1.0;
        listOfScreenCorners[i][2].y = 1.0;

        listOfScreenCorners[i][3].x = 0.0;
        listOfScreenCorners[i][3].y = 1.0;
    }

    SampleFactory factory;
    samples = factory.createSamples();

    for (int j=0; j<MAX_SCREENS; j++) {
        for (int i=0; i<MAX_LAYERS; i++) {
            screenLayerSettings[j][i].selectedSampleIndex = 0;
        }
    }

    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofHideCursor();

    midiIn.listInPorts();
    midiIn.openPort(1);
    //midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);
    midiIn.setVerbose(true);

    ofSetFrameRate(30);
    string qwerty = "qwertyuiopasdfghjklzxcvbnm";
    for (int i=0; i< qwerty.size(); i++) {
        keysToIndex[qwerty.at(i)-'a'] = i;
    }
    // start playing first sample in first screen on first  by default

    this->keyPressed('!');
    selectSampleIndex(0);
}

ofPooks::~ofPooks() {
    for (int i=0; i< samples.size(); i++) {
        delete samples.at(i);
    }
    for (int i=0; i< colorChannels.size(); i++) {
        delete colorChannels.at(i);
    }
    for (int i=0; i< layouts.size(); i++) {
        delete layouts.at(i);
    }

}

void ofPooks::loadLayouts() {
    layouts.push_back(new LayoutTelevision());
    layouts.push_back(new LayoutGrid());
    layouts.push_back(new LayoutGridDynamic());
    layouts.push_back(new LayoutVerticalStripes());
    layouts.push_back(new LayoutHorizontalStripes());
    layouts.push_back(new LayoutStarryNight());
    layouts.push_back(new LayoutGridVerticalNoisy());
    layouts.push_back(new LayoutGridHorizontalNoisy());
}

void ofPooks::loadColors() {
    //    ofDirectory textDir = ofFilePath::join(ofFilePath::getUserHomeDir(), "Movies/Pooks/text/");
    //    ofLog(OF_LOG_NOTICE, "loading colorchannels...");
    //    if (textDir.exists() && textDir.isDirectory()) {
    //        ofLog(OF_LOG_NOTICE, "[" + textDir.path() + "] exists and has [" + ofToString(textDir.listDir()) + "] files.");
    //        vector<ofFile> files = textDir.getFiles();
    //        for (vector<ofFile>::iterator it = files.begin(); it!=files.end(); ++it) {
    //            ofFile file = *it;
    //            ofLog(OF_LOG_NOTICE, "found text file [" + file.path() + "]");
    //            colorChannels.push_back(new ColorChannelPoem(file.path()));
    //            colorChannels.push_back(new ColorChannelPoemNoRepetitions(file.path()));
    //        }
    //    }
    //    ofLog(OF_LOG_NOTICE, "loading colorchannels done.");

    ColorChannel *colorChannel = new ColorChannel();
    colorChannel->loadColors();
    colorChannels.push_back(colorChannel);

    ColorChannelAlphabet *alphabet = new ColorChannelAlphabet();
    alphabet->loadColors();
    colorChannels.push_back(alphabet);

    ColorChannel *colorChannelBlack = new ColorChannelPassthrough();
    colorChannelBlack->loadColors();
    colorChannels.push_back(colorChannelBlack);

    ofLog(OF_LOG_NOTICE, "loading colorchannels done.");
}

void ofPooks::exit() {
    midiIn.closePort();
}

//--------------------------------------------------------------
void ofPooks::update(){
    ofBackground(0, 0, 0);

    for (int i=0; i<samples.size(); i++) {
        Sample sample = *samples[i];
        if (sample.getActiveCount() > 0 && !sample.isPlaying()) {
            sample.play();
        } else if (sample.getActiveCount() == 0 && sample.isPlaying()) {
            sample.stop();
        }

        if (sample.isPlaying()) {
            sample.update();
        }
    }

    for (int  i=0; i<MAX_SCREENS; i++) {
        for (int j=0; j<MAX_LAYERS; j++) {
            Layer layer = screenLayerSettings[i][j];
            Layout *layout = layouts.at(layer.selectedLayoutIndex % layouts.size());
            layout->update(layer);
            float speed = masterVolume == 0 ? 0.0 : layer.speed;
            if (layer.selectedSampleIndex < samples.size()) {
                samples[layer.selectedSampleIndex]->setSpeed(speed);
            }
        }
    }
}

//--------------------------------------------------------------
void ofPooks::draw(){
    for(int i=0; i<MAX_SCREENS; i++) {
        ofPushMatrix();
        warpScreen(i);
        renderScreen(i);
        if (showWarpTool) {
            renderWarpTool(i+1);
        }
        ofPopMatrix();
        if (showWarpTool) {
            ofSetHexColor(0xFFFFFF);
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofDrawCircle(mousePos.x, mousePos.y,  15);
            ofSetRectMode(OF_RECTMODE_CORNER);
        }
    }
}

void ofPooks::renderScreen(int screenIndex) {
    Editable screen = screenSettings[screenIndex];
    if (screen.alpha > 0.0) {
        float masterScreenAlpha = screen.alpha * masterAlpha;
        for (int i=0; i<MAX_LAYERS; i++) {
            Layer layer = screenLayerSettings[screenIndex][i];
            layer.masterScreenAlpha = masterScreenAlpha;
            if (layer.alpha > 0.0 && layer.selectedSampleIndex < samples.size()) {
                // one texture per layer
                Sample *sample = samples[layer.selectedSampleIndex];
                // one colorChannel per layer
                ColorChannel *colorChannel = colorChannels.at(layer.selectedColorIndex);
                if (sample->isVideoPlayer || sample->isVideoGrabber) {
                    if (sample->isPlaying()) {
                        if (sample->isFrameNew()) {
                            sample->cacheTextureReference();
                        }
                        ofTexture texture = sample->getTextureReference();

                        ofEnableAlphaBlending();
                        int selectedIndex = layer.selectedLayoutIndex;
                        Layout *layout = layouts[selectedIndex % layouts.size()];
                        layout->render(texture, colorChannel, layer);
                        ofDisableAlphaBlending();
                    }
                }
            }
        }
    }
}

void ofPooks::warpScreen(int screenIndex) {
    ofPoint corners[4];
    for (int i=0; i<4; i++) {
        corners[i] = listOfScreenCorners[screenIndex][i];
    }
    //lets make a matrix for openGL
    //this will be the matrix that peforms the transformation
    GLfloat myMatrix[16];

    //we set it to the default - 0 translation
    //and 1.0 scale for x y z and w
    for(int i = 0; i < 16; i++){
        if(i % 5 != 0) myMatrix[i] = 0.0;
        else myMatrix[i] = 1.0;
    }

    //we need our points as opencv points
    //be nice to do this without opencv?
    //CvPoint2D32f cvsrc[4];
    //CvPoint2D32f cvdst[4];

    //we set the warp coordinates
    //source coordinates as the dimensions of our window
    //cvsrc[0].x = 0;
    //cvsrc[0].y = 0;
    //cvsrc[1].x = ofGetWidth();
    //cvsrc[1].y = 0;
    //cvsrc[2].x = ofGetWidth();
    //cvsrc[2].y = ofGetHeight();
    //cvsrc[3].x = 0;
    //cvsrc[3].y = ofGetHeight();

    //corners are in 0.0 - 1.0 range
    //so we scale up so that they are at the window's scale
    //for(int i = 0; i < 4; i++){
    //    cvdst[i].x = corners[i].x * (float)ofGetWidth();
    //    cvdst[i].y = corners[i].y * (float)ofGetHeight();
    //}

}

void ofPooks::renderWarpTool(int screenNumber) {
    int hexColor = selectedScreen == screenNumber ? 0xFFFFFF : 0xFFFF00;

    //lets draw a bounding box
    ofNoFill();
    ofSetHexColor(hexColor);
    ofDrawRectangle(1, 1, ofGetWidth()-2, ofGetHeight()-2);

    //our particles
    ofEnableAlphaBlending();
    ofSetHexColor(hexColor);
    ofFill();

    ofSetRectMode(OF_RECTMODE_CENTER);
    ofDrawCircle(mousePos.x, mousePos.y,  20);
    ofSetRectMode(OF_RECTMODE_CORNER);

    ofDisableAlphaBlending();

    char selectedScreenMsg[255];
    sprintf(selectedScreenMsg, "Screen %d", screenNumber);


    ofSetHexColor(hexColor);
    ttf.drawString(selectedScreenMsg, ofGetWidth()/3.0f, ofGetHeight()/2.0f);

    ofSetHexColor(0x000000);
    ttf2.drawString(msg, 78, 433);

    ofSetHexColor(hexColor);
    ttf2.drawString(msg, 80, 430);







}

void ofPooks::newMidiMessage(ofxMidiMessage& midiMsg) {

    // store some data from midi message in variables
    control = midiMsg.control;
    value = midiMsg.value;
    channel = midiMsg.channel;


    sprintf(msg, "value: (%i,%i), received from port: %i, id: %i \n\nwith %f milliseconds difference from last message",control,value,port,channel,timestamp);
    ofLog(OF_LOG_NOTICE, "%s", msg);

    float normValue2 = value / 127.0f;
    if (control == 0) {
        int newSampleIndex = normValue2 * (samples.size() - 1);
        selectSampleIndex(newSampleIndex);
    } else if (control == 1) {
        for (int j=0; j<MAX_SCREENS;j++) {
            if (screenSettings[j].canEdit) {
                for (int i=0; i< MAX_LAYERS; i++) {
                    if (screenLayerSettings[j][i].canEdit) {
                        screenLayerSettings[j][i].complexity = normValue2;
                    }
                }
            }
        }
    } else if (control == 2) {
        for (int j=0; j<MAX_SCREENS;j++) {
            if (screenSettings[j].canEdit) {
                for (int i=0; i< MAX_LAYERS; i++) {
                    if (screenLayerSettings[j][i].canEdit) {
                        screenLayerSettings[j][i].selectedLayoutIndex = normValue2 * (MAX_LAYOUTS-1);
                    }
                }
            }
        }
    } else if (control == 3) {
        for (int j=0; j<MAX_SCREENS;j++) {
            if (screenSettings[j].canEdit) {
                for (int i=0; i< MAX_LAYERS; i++) {
                    if (screenLayerSettings[j][i].canEdit) {
                        screenLayerSettings[j][i].luminance = normValue2;
                    }
                }
            }
        }
    } else if (control == 4) {
        for (int j=0; j<MAX_SCREENS;j++) {
            if (screenSettings[j].canEdit) {
                for (int i=0; i< MAX_LAYERS; i++) {
                    if (screenLayerSettings[j][i].canEdit) {
                        screenLayerSettings[j][i].alpha = normValue2;
                    }
                }
            }
        }
    } else if (control == 5) {
        int index = normValue2 * (colorChannels.size() - 1);
        for (int j=0; j<MAX_SCREENS;j++) {
            if (screenSettings[j].canEdit) {
                for (int i=0; i< MAX_LAYERS; i++) {
                    if (screenLayerSettings[j][i].canEdit) {
                        screenLayerSettings[j][i].selectedColorIndex = index;
                    }
                }
            }
        }
    } else if (control == 6) {
        for (int j=0; j<MAX_SCREENS;j++) {
            if (screenSettings[j].canEdit) {
                for (int i=0; i< MAX_LAYERS; i++) {
                    if (screenLayerSettings[j][i].canEdit) {
                        screenLayerSettings[j][i].speed = normValue2;
                    }
                }
            }
        }
    } else if (control == 7) {
        for (int j=0; j<MAX_SCREENS;j++) {
            if (screenSettings[j].canEdit) {
                for (int i=0; i< MAX_LAYERS; i++) {
                    if (screenLayerSettings[j][i].canEdit) {
                        screenLayerSettings[j][i].layoutSpeed = normValue2;
                    }
                }
            }
        }
    } else if (control == 32) {
        screenSettings[0].canEdit = normValue2 == 1.0f;
    } else if (control == 33) {
        screenSettings[1].canEdit = normValue2 == 1.0f;
    } else if (control == 34) {
        screenSettings[2].canEdit = normValue2 == 1.0f;
    } else if (control == 35) {
        screenSettings[3].canEdit = normValue2 == 1.0f;
    } else if (control == 36) {
        screenSettings[4].canEdit = normValue2 == 1.0f;
    } else if (control == 37) {
        screenSettings[5].canEdit = normValue2 == 1.0f;
    } else if (control >= 16 && control < (16 + MAX_SCREENS)) {
        if (screenSettings[control-16].canEdit) {
            screenSettings[control-16].alpha = normValue2;
        }
    } else if (control >= 48 && control < 48 + MAX_LAYERS) {
        for (int i=0; i<MAX_SCREENS; i++) {
            if (screenSettings[i].canEdit) {
                screenLayerSettings[i][control - 48].canEdit = normValue2 == 1.0;
            }
        }
    } else if (control == 23) {
        masterAlpha = normValue2;
        masterVolume = normValue2;
    }
    port = midiMsg.portNum;
    timestamp = midiMsg.deltatime;
}

void ofPooks::selectColorChannelIndex(int colorChannelIndex) {
    for (int j=0; j<MAX_SCREENS;j++) {
        if (screenSettings[j].canEdit) {
            for (int i=0; i< MAX_LAYERS; i++) {
                if (screenLayerSettings[j][i].canEdit) {
                    screenLayerSettings[j][i].selectedColorIndex = colorChannelIndex % colorChannels.size();
                }
            }
        }
    }
}

void ofPooks::selectSampleIndex(int newSampleIndex) {
    if (newSampleIndex < samples.size()) {
        for (int j=0; j<MAX_SCREENS;j++) {
            if (screenSettings[j].canEdit) {
                for (int i=0; i< MAX_LAYERS; i++) {
                    if (screenLayerSettings[j][i].canEdit) {
                        int oldSampleIndex = screenLayerSettings[j][i].selectedSampleIndex;
                        Sample* oldSample = samples.at(oldSampleIndex);
                        oldSample->decreaseActiveCount();

                        screenLayerSettings[j][i].selectedSampleIndex = newSampleIndex;
                        Sample *newSample = samples.at(newSampleIndex);
                        newSample->increaseActiveCount();
                    }
                }
            }
        }
    }
}


//--------------------------------------------------------------
void ofPooks::keyPressed(int key){
    if (key == 'F') {
        ofToggleFullscreen();
    } else if (key > '0' && key < '7') {
        whichCorner = 0;
        int affectedScreen = key - '0';
        if (affectedScreen == selectedScreen) {
            showWarpTool = !showWarpTool;
        } else {
            selectedScreen = affectedScreen;
            showWarpTool = true;
        }
        if (showWarpTool) {
            ofShowCursor();
        } else {
            ofHideCursor();
        }
    } else {

        if (key - 'a' < 26 && key - 'a' >= 0) {
            selectSampleIndex(keysToIndex[key - 'a']);
        } else if (key >= 0 && key < 26) {
            selectColorChannelIndex(keysToIndex[key]);
        } else {
            switch(key) {

            case 'Z':
                for (int i=0; i<MAX_SCREENS; i++) {
                    bool active = keyboardController.isScreenActive(i);
                    if (active) {
                        screenLayerSettings[i][0].speed = screenLayerSettings[i][0].speed > 0.0f ? 0.0f : 1.0f;
                    }
                }
                break;
            case 'A':
                masterAlpha = masterAlpha < 0.1f ? 0.0f : (masterAlpha - 0.1f);
                break;
            case 'S':
                masterAlpha = masterAlpha > 0.9f ? 1.0f : (masterAlpha + 0.1f);
                break;
            case 'Q':
                for (int i=0; i<MAX_SCREENS; i++) {
                    bool active = keyboardController.isScreenActive(i);
                    if (active) {
                        screenLayerSettings[i][0].selectedLayoutIndex = (screenLayerSettings[i][0].selectedLayoutIndex + 1) % MAX_LAYOUTS;
                    }
                }
                break;
            case 'W':
                for (int i=0; i<MAX_SCREENS; i++) {
                    bool active = keyboardController.isScreenActive(i);
                    if (active) {
                        float complexity = screenLayerSettings[i][0].complexity;
                        screenLayerSettings[i][0].complexity = complexity < 0.1f ? 0.0f : (complexity - 0.1f);
                    }
                }
                break;
            case 'E':
                for (int i=0; i<MAX_SCREENS; i++) {
                    bool active = keyboardController.isScreenActive(i);
                    if (active) {
                        float complexity = screenLayerSettings[i][0].complexity;
                        screenLayerSettings[i][0].complexity = complexity > 0.9f ? 0.0f : (complexity + 0.1f);
                    }
                }
                break;

            default:
                keyboardController.keyPressed(key);
                for (int i=0; i<MAX_SCREENS; i++) {
                    bool active = keyboardController.isScreenActive(i);
                    screenSettings[i].canEdit = active;
                    screenSettings[i].alpha = active ? masterAlpha : 0.0;

                    screenLayerSettings[i][0].canEdit = active;
                    screenLayerSettings[i][0].alpha = active ? 1.0 : 0.0;
                }
                break;
            }
        }

    }
}

//--------------------------------------------------------------
void ofPooks::keyReleased(int key){

}

//--------------------------------------------------------------
void ofPooks::mouseMoved(int x, int y ){
    mousePos.x = x;
    mousePos.y = y;
}

//--------------------------------------------------------------
void ofPooks::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofPooks::mousePressed(int x, int y, int button){
    if (showWarpTool) {
        whichCorner = whichCorner % 4;
        float scaleX = (float)x / ofGetWidth();
        float scaleY = (float)y / ofGetHeight();
        listOfScreenCorners[selectedScreen-1][whichCorner].x = scaleX;
        listOfScreenCorners[selectedScreen-1][whichCorner].y = scaleY;
        whichCorner++;
    }
}

//--------------------------------------------------------------
void ofPooks::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofPooks::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofPooks::gotMessage(ofMessage midiMsg){

}

//--------------------------------------------------------------
void ofPooks::dragEvent(ofDragInfo dragInfo){

}
