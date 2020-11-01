#include "pooksApp.h"
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

void pooksApp::setup() {
    // ensure to load from app bundle resources
    ofSetDataPathRoot("../Resources/");
    
    //loads load in some truetype fonts

	ttf.loadFont("frabk.ttf", 80);
	ttf2.loadFont("frabk.ttf", 14);

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
	
	midiIn.setVerbose(false);
	midiIn.listInPorts();
	midiIn.openPort(1);
	midiIn.addListener(this);
	
	ofSetFrameRate(30);
    string qwerty = "qwertyuiopasdfghjklzxcvbnm";
    for (int i=0; i< qwerty.size(); i++) {
        keysToIndex[qwerty.at(i)-'a'] = i;
    }
    // start playing first sample in first screen on first  by default

    this->keyPressed('!');
    selectSampleIndex(0);
}

pooksApp::~pooksApp() {
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

void pooksApp::loadLayouts() {
    layouts.push_back(new LayoutTelevision());
    layouts.push_back(new LayoutGrid());
    layouts.push_back(new LayoutGridDynamic());
    layouts.push_back(new LayoutVerticalStripes());
    layouts.push_back(new LayoutHorizontalStripes());
    layouts.push_back(new LayoutStarryNight());
    layouts.push_back(new LayoutGridVerticalNoisy());
    layouts.push_back(new LayoutGridHorizontalNoisy());
}

void pooksApp::loadColors() {
    string userDir = ofFilePath::getUserHomeDir();
    ofDirectory textDir(ofFilePath::join(userDir, "Movies/Pooks/text/"));
    ofLog(OF_LOG_NOTICE, "loading colorchannels...");
    if (textDir.exists() && textDir.isDirectory()) {
        ofLog(OF_LOG_NOTICE, "[" + textDir.path() + "] exists and has [" + ofToString(textDir.listDir()) + "] files.");
        vector<ofFile> files = textDir.getFiles();
        for (vector<ofFile>::iterator it = files.begin(); it!=files.end(); ++it) {
            ofFile file = *it;
            ofLog(OF_LOG_NOTICE, "found text file [" + file.path() + "]");
            colorChannels.push_back(new ColorChannelPoem(file.path()));
            colorChannels.push_back(new ColorChannelPoemNoRepetitions(file.path()));
        }
    }
    ofLog(OF_LOG_NOTICE, "loading colorchannels done.");
    
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

void pooksApp::exit() {
	midiIn.closePort();
}

//--------------------------------------------------------------
void pooksApp::update(){
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
void pooksApp::draw(){
	for(int i=0; i<MAX_SCREENS; i++) {
		ofPushMatrix();
		//warpScreen(i);
		renderScreen(i);
		if (showWarpTool) {
			renderWarpTool(i+1);
		}
		ofPopMatrix();
		if (showWarpTool) {
			ofSetHexColor(0xFFFFFF);
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofCircle(mousePos.x, mousePos.y,  15);
			ofSetRectMode(OF_RECTMODE_CORNER);
		}
	}
}

void pooksApp::renderScreen(int screenIndex) {
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

void pooksApp::warpScreen(int screenIndex) {
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
	CvPoint2D32f cvsrc[4];
	CvPoint2D32f cvdst[4];
	
	//we set the warp coordinates
	//source coordinates as the dimensions of our window
	cvsrc[0].x = 0;
	cvsrc[0].y = 0;
	cvsrc[1].x = ofGetWidth();
	cvsrc[1].y = 0;
	cvsrc[2].x = ofGetWidth();
	cvsrc[2].y = ofGetHeight();
	cvsrc[3].x = 0;
	cvsrc[3].y = ofGetHeight();
	
	//corners are in 0.0 - 1.0 range
	//so we scale up so that they are at the window's scale
	for(int i = 0; i < 4; i++){
		cvdst[i].x = corners[i].x * (float)ofGetWidth();
		cvdst[i].y = corners[i].y * (float)ofGetHeight();
	}
	
	//we create a matrix that will store the results
	//from openCV - this is a 3x3 2D matrix that is
	//row ordered
	CvMat * translate = cvCreateMat(3,3,CV_32FC1);
	
	//this is the slightly easier - but supposidly less
	//accurate warping method
	//cvWarpPerspectiveQMatrix(cvsrc, cvdst, translate);
	
	
	//for the more accurate method we need to create
	//a couple of matrixes that just act as containers
	//to store our points  - the nice thing with this
	//method is you can give it more than four points!
	
	CvMat* src_mat = cvCreateMat( 4, 2, CV_32FC1 );
	CvMat* dst_mat = cvCreateMat( 4, 2, CV_32FC1 );
	
	//copy our points into the matrixes
	cvSetData( src_mat, cvsrc, sizeof(CvPoint2D32f));
	cvSetData( dst_mat, cvdst, sizeof(CvPoint2D32f));
	
	//figure out the warping!
	//warning - older versions of openCV had a bug
	//in this function.
	//cvFindHomography(src_mat, dst_mat, translate);
	
	//get the matrix as a list of floats
	float *matrix = translate->data.fl;
	
	
	//we need to copy these values
	//from the 3x3 2D openCV matrix which is row ordered
	//
	// ie:   [0][1][2] x
	//       [3][4][5] y
	//       [6][7][8] w
	
	//to openGL's 4x4 3D column ordered matrix
	//        x  y  z  w
	// ie:   [0][3][ ][6]
	//       [1][4][ ][7]
	//		 [ ][ ][ ][ ]
	//       [2][5][ ][9]
	//
	
	myMatrix[0]		= matrix[0];
	myMatrix[4]		= matrix[1];
	myMatrix[12]	= matrix[2];
	
	myMatrix[1]		= matrix[3];
	myMatrix[5]		= matrix[4];
	myMatrix[13]	= matrix[5];
	
	myMatrix[3]		= matrix[6];
	myMatrix[7]		= matrix[7];
	myMatrix[15]	= matrix[8];
	
	
	//finally lets multiply our matrix
	//wooooo hoooo!
	glMultMatrixf(myMatrix);
}

void pooksApp::renderWarpTool(int screenNumber) {
	int hexColor = selectedScreen == screenNumber ? 0xFFFFFF : 0xFFFF00;
	
	//lets draw a bounding box
	ofNoFill();
	ofSetHexColor(hexColor);
	ofRect(1, 1, ofGetWidth()-2, ofGetHeight()-2);
	
	//our particles
	ofEnableAlphaBlending();
	ofSetHexColor(hexColor);
	ofFill();
	
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofCircle(mousePos.x, mousePos.y,  20);
	ofSetRectMode(OF_RECTMODE_CORNER);
	
	ofDisableAlphaBlending();
	
	char selectedScreenMsg[255];
	sprintf(selectedScreenMsg, "Screen %d", screenNumber);
    
	
	ofSetHexColor(hexColor);
	ttf.drawString(selectedScreenMsg, ofGetWidth()/3.0, ofGetHeight()/2.0);
    
	ofSetHexColor(0x000000);
	ttf2.drawString(msg, 78, 433);
	
	ofSetHexColor(hexColor);
	ttf2.drawString(msg, 80, 430);
    
    
    
    
    
    
    
}

void pooksApp::newMidiMessage(ofxMidiMessage& eventArgs) {
	
	// store some data from midi message in variables
	value = eventArgs.value;
	value2 = eventArgs.velocity;
	id = eventArgs.channel;
	
	sprintf(msg, "value: (%i,%i), received from port: %i, id: %i \n\nwith %f milliseconds difference from last message",value,value2,port,id,timestamp);
	
	float normValue2 = value2 / 127.0;
	if (id == 1 && value == 7) {
        int newSampleIndex = normValue2 * (samples.size() - 1);
        selectSampleIndex(newSampleIndex);
	} else if (id == 2 && value == 7) {
		for (int j=0; j<MAX_SCREENS;j++) {
			if (screenSettings[j].canEdit) {
				for (int i=0; i< MAX_LAYERS; i++) {
					if (screenLayerSettings[j][i].canEdit) {
						screenLayerSettings[j][i].complexity = normValue2;
					}
				}
			}
		}
	} else if (id == 3 && value == 7) {
		for (int j=0; j<MAX_SCREENS;j++) {
			if (screenSettings[j].canEdit) {
				for (int i=0; i< MAX_LAYERS; i++) {
					if (screenLayerSettings[j][i].canEdit) {
						screenLayerSettings[j][i].selectedLayoutIndex = normValue2 * (MAX_LAYOUTS-1);
					}
				}
			}
		}
	} else if (id == 4 && value == 7) {
		for (int j=0; j<MAX_SCREENS;j++) {
			if (screenSettings[j].canEdit) {
				for (int i=0; i< MAX_LAYERS; i++) {
					if (screenLayerSettings[j][i].canEdit) {
						screenLayerSettings[j][i].luminance = normValue2;
					}
				}
			}
		}
	} else if (id == 5 && value == 7) {
		for (int j=0; j<MAX_SCREENS;j++) {
			if (screenSettings[j].canEdit) {
				for (int i=0; i< MAX_LAYERS; i++) {
					if (screenLayerSettings[j][i].canEdit) {
						screenLayerSettings[j][i].alpha = normValue2;
					}
				}
			}
		}
	} else if (id == 6 && value == 7) {
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
	} else if (id == 7 && value == 7) {
		for (int j=0; j<MAX_SCREENS;j++) {
			if (screenSettings[j].canEdit) {
				for (int i=0; i< MAX_LAYERS; i++) {
					if (screenLayerSettings[j][i].canEdit) {
						screenLayerSettings[j][i].speed = normValue2;
					}
				}
			}
		}
	} else if (id == 8 && value == 7) {
		for (int j=0; j<MAX_SCREENS;j++) {
			if (screenSettings[j].canEdit) {
				for (int i=0; i< MAX_LAYERS; i++) {
					if (screenLayerSettings[j][i].canEdit) {
						screenLayerSettings[j][i].layoutSpeed = normValue2;
					}
				}
			}
		}
	} else if (id == 1) {
		if (value == 47) {
			screenSettings[0].canEdit = normValue2 == 1.0;
		} else if (value == 45) {
			screenSettings[1].canEdit = normValue2 == 1.0;
		} else if (value == 48) {
			screenSettings[2].canEdit = normValue2 == 1.0;
		} else if (value == 49) {
			screenSettings[3].canEdit = normValue2 == 1.0;
		} else if (value == 46) {
			screenSettings[4].canEdit = normValue2 == 1.0;
		} else if (value == 44) {
			screenSettings[5].canEdit = normValue2 == 1.0;
		}
		
	}
	
	if (value == 10) {
		if (id > 0 && id <= MAX_SCREENS) {
			if (screenSettings[id-1].canEdit) {
				screenSettings[id-1].alpha = normValue2;
			}
		} else if (id == 9) {
            masterAlpha = normValue2;
            masterVolume = normValue2;
        }
	}
	
	if (value == 16) {
		for (int i=0; i<MAX_SCREENS; i++) {
			if (screenSettings[i].canEdit) {
				int controlNo = id;
				if (id > 0 && id <= MAX_LAYERS) {
					screenLayerSettings[i][id-1].canEdit = normValue2 == 1.0;
				}
			}
		}
	}
	port = eventArgs.portNum;
	timestamp = eventArgs.deltatime;
}

void pooksApp::selectColorChannelIndex(int colorChannelIndex) {
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

void pooksApp::selectSampleIndex(int newSampleIndex) {
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
void pooksApp::keyPressed(int key){
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
                        screenLayerSettings[i][0].speed = screenLayerSettings[i][0].speed > 0.0 ? 0.0 : 1.0;
                    }
                }
                break;
            case 'A':
                masterAlpha = masterAlpha < 0.1 ? 0.0 : (masterAlpha - 0.1);
                break;
            case 'S':
                masterAlpha = masterAlpha > 0.9 ? 1.0 : (masterAlpha + 0.1);
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
                        screenLayerSettings[i][0].complexity = complexity < 0.1 ? 0.0 : (complexity - 0.1);
                    }
                }
                break;
            case 'E':
                for (int i=0; i<MAX_SCREENS; i++) {
                    bool active = keyboardController.isScreenActive(i);
                    if (active) {
                        float complexity = screenLayerSettings[i][0].complexity;
                        screenLayerSettings[i][0].complexity = complexity > 0.9 ? 0.0 : (complexity + 0.1);
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
void pooksApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void pooksApp::mouseMoved(int x, int y ){
	mousePos.x = x;
	mousePos.y = y;
}

//--------------------------------------------------------------
void pooksApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void pooksApp::mousePressed(int x, int y, int button){
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
void pooksApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void pooksApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void pooksApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void pooksApp::dragEvent(ofDragInfo dragInfo){
	
}
