#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	// black
	colors[0].set(0, 0, 0);
	// royal yellow
	colors[1].set(250, 218, 94);
	// burnt orange
	colors[2].set(204, 85, 0);
	// yellow gold
	colors[3].set(255, 215, 0);
	// light sea green
	colors[4].set(230, 0, 0);
	// chinese red
	colors[5].set(230, 0, 0);
	// chinese red (subsidiary 1)
	colors[6].set(254, 40, 14);
	// chinese red (subsidiary 2)
	colors[7].set(242, 85, 0);
	// chinese red (subsidiary 3)
	colors[8].set(137, 0, 24);
	
	selectedScreen = 0;
	showWarpTool = false;
    
	
	//we run at 60 fps!
	ofSetVerticalSync(true);
	
	//loads load in some truetype fonts
	ttf.loadFont("type/frabk.ttf", 80);
	ttf2.loadFont("type/frabk.ttf", 14);
	
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
	
	loadSamples();
	for (int j=0; j<MAX_SCREENS; j++) {
		for (int i=0; i<MAX_LAYERS; i++) {
			screenLayerSettings[j][i].selectedSampleIndex = 0;
		}
	}
	
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofHideCursor();
	
	midiIn.setVerbose(false);
	midiIn.listPorts();
	midiIn.openPort(0);
	midiIn.addListener(this);	
	
	shader.setup(320,240);
	ofSetFrameRate(30);
}

// TODO - color, layers, speed adjustment with each layer / layouts, master control
// valerie - start with slow urban, speed up abstract urban mix in valerie, iamman face

void testApp::loadSamples() {
    //loadSamplesNoReservations();
    loadSamplesValerie();
    loadSamplesLolita();
    loadSamplesShi();
}

void testApp::loadSamplesLolita() {
    samples[0].loadMovie("/Users/jorrit/Movies/shows/assassins2012/lolita/iAmNotSorry1954.mov");
	samples[0].setUseTexture(true);
    
    samples[1].loadMovie("/Users/jorrit/Movies/shows/assassins2012/lolita/libreEstaNoche1979.mov");
	samples[1].setUseTexture(true);
    
    samples[2].loadMovie("/Users/jorrit/Movies/shows/assassins2012/lolita/lolitaChair1954.mov");
	samples[2].setUseTexture(true);
    
    samples[3].loadMovie("/Users/jorrit/Movies/shows/assassins2012/lolita/lolitaHeadshotNoSound1954.mov");
	samples[3].setUseTexture(true);
    
    samples[4].loadMovie("/Users/jorrit/Movies/shows/assassins2012/lolita/lolitaInterviewNoSound1954.mov");
	samples[4].setUseTexture(true);
    
    samples[5].loadMovie("/Users/jorrit/Movies/shows/assassins2012/lolita/iAmNotSorry1954.mov");
	samples[5].setUseTexture(true);
    
    samples[6].loadMovie("/Users/jorrit/Movies/shows/assassins2012/lolita/iAmNotSorry1954.mov");
	samples[6].setUseTexture(true);
    
    samples[7].loadMovie("/Users/jorrit/Movies/shows/assassins2012/lolita/iAmNotSorry1954.mov");
	samples[7].setUseTexture(true);
    
    samples[8].loadMovie("/Users/jorrit/Movies/shows/assassins2012/lolita/iAmNotSorry1954.mov");
	samples[8].setUseTexture(true);
    
    samples[9].loadMovie("/Users/jorrit/Movies/shows/assassins2012/lolita/birds.mov");
	samples[9].setUseTexture(true);
    
    samples[10].loadMovie("/Users/jorrit/Movies/shows/assassins2012/lolita/birds.mov");
	samples[10].setUseTexture(true);
    
    samples[11].loadMovie("/Users/jorrit/Movies/shows/assassins2012/lolita/lolitaArrestStill.mov");
	samples[11].setUseTexture(true);
    
    samples[12].loadMovie("/Users/jorrit/Movies/shows/assassins2012/lolita/movingPoints.mov");
	samples[12].setUseTexture(true);
    
	
}

void testApp::loadSamplesNoReservations() {
    
    samples[0].loadMovie("/Users/jorrit/Movies/shows/noReservationsJai2012/noReservationsEdit.mov");
	samples[0].setUseTexture(true);
	
    samples[1].loadMovie("/Users/jorrit/Movies/shows/noReservationsJai2012/noReservationsEdit.mov");
	samples[1].setUseTexture(true);
	
    samples[2].loadMovie("/Users/jorrit/Movies/shows/noReservationsJai2012/noReservationsEdit.mov");
	samples[2].setUseTexture(true);
	
    samples[3].loadMovie("/Users/jorrit/Movies/shows/noReservationsJai2012/noReservationsEdit.mov");
	samples[3].setUseTexture(true);
	
    samples[4].loadMovie("/Users/jorrit/Movies/shows/noReservationsJai2012/noReservationsEdit.mov");
	samples[4].setUseTexture(true);
	
    samples[5].loadMovie("/Users/jorrit/Movies/shows/noReservationsJai2012/noReservationsEdit.mov");
	samples[5].setUseTexture(true);
	
    samples[6].loadMovie("/Users/jorrit/Movies/shows/noReservationsJai2012/noReservationsEdit.mov");
	samples[6].setUseTexture(true);
	
    samples[7].loadMovie("/Users/jorrit/Movies/shows/noReservationsJai2012/noReservationsEdit.mov");
	samples[7].setUseTexture(true);
    
    samples[8].loadMovie("/Users/jorrit/Movies/shows/noReservationsJai2012/noReservationsEdit.mov");
	samples[8].setUseTexture(true);
    
    samples[9].loadMovie("/Users/jorrit/Movies/shows/noReservationsJai2012/noReservationsEdit.mov");
	samples[9].setUseTexture(true);
    
    samples[10].loadMovie("/Users/jorrit/Movies/shows/noReservationsJai2012/noReservationsEdit.mov");
	samples[10].setUseTexture(true);
    
    samples[11].loadMovie("/Users/jorrit/Movies/shows/noReservationsJai2012/noReservationsEdit.mov");
	samples[11].setUseTexture(true);
    
    samples[12].loadMovie("/Users/jorrit/Movies/samples/abstract/whitePaint320x240.mov");
	samples[12].setUseTexture(true);
    
}

void testApp::loadSamplesValerie() {
    
    samples[13].loadMovie("/Users/jorrit/Movies/shows/assassins2012/valerie/piStreet.mov");
	samples[13].setUseTexture(true);
	
	samples[14].loadMovie("/Users/jorrit/Movies/shows/assassins2012/valerie/piStreet.mov");
	samples[14].setUseTexture(true);
	
    samples[15].loadMovie("/Users/jorrit/Movies/shows/assassins2012/valerie/valerieHeadshot.mov");
	samples[15].setUseTexture(true);
    
    samples[16].loadMovie("/Users/jorrit/Movies/shows/assassins2012/valerie/iAManCloseup.avi");
	samples[16].setUseTexture(true);
    
    samples[17].loadMovie("/Users/jorrit/Movies/shows/assassins2012/valerie/windows3.avi");
	samples[17].setUseTexture(true);
    
    fileBuffer = ofBufferFromFile("/Users/jorrit/Movies/shows/assassins2012/valerie/scum.txt");
}

void testApp::loadSamplesShi() {
    samples[18].loadMovie("/Users/jorrit/Movies/shows/assassins2012/shi/completeZoomout.mov");
	samples[18].setUseTexture(true);
	
	samples[19].loadMovie("/Users/jorrit/Movies/shows/assassins2012/shi/shiPortrait.mov");
	samples[19].setUseTexture(true);

    samples[20].loadMovie("/Users/jorrit/Movies/shows/assassins2012/shi/handsFinalColumns.mov");
	samples[20].setUseTexture(true);
    
    samples[21].loadMovie("/Users/jorrit/Movies/shows/assassins2012/shi/handsFirstColumn.mov");
	samples[21].setUseTexture(true);
    
    samples[22].loadMovie("/Users/jorrit/Movies/shows/assassins2012/shi/handsFourColumns.mov");
	samples[22].setUseTexture(true);
    
    samples[23].loadMovie("/Users/jorrit/Movies/shows/assassins2012/shi/handsSeventhColumn.mov");
	samples[23].setUseTexture(true);

    samples[24].loadMovie("/Users/jorrit/Movies/shows/assassins2012/shi/movingCharacters.mov");
	samples[24].setUseTexture(true);

    samples[25].loadMovie("/Users/jorrit/Movies/shows/assassins2012/shi/movingCharactersCloseup.mov");
	samples[25].setUseTexture(true);
    
}

void testApp::exit() {
	midiIn.closePort();
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(0, 0, 0);
	
	for (int i = 0; i < MAX_SAMPLES; i++) {
		if (sampleActiveCount[i] > 0 && !samples[i].isPlaying()) {
			samples[i].play();
		} else if (sampleActiveCount[i] == 0 && samples[i].isPlaying()) {
			samples[i].stop();
		}
		
		if (samples[i].isPlaying()) {
			samples[i].update();
		} 
	}
	
	for (int  i=0; i<MAX_SCREENS; i++) {
		for (int j=0; j<MAX_LAYERS; j++) {
            Layer layer = screenLayerSettings[i][j];
            if (layer.selectedLayoutIndex == 1) {
				for (int k=0; k<MAX_STARS; k++) {
					stars[k].update();
				}
			}
            float speed = masterVolume == 0 ? 0.0 : layer.speed;
            samples[layer.selectedSampleIndex].setSpeed(speed);
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
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
			ofCircle(mousePos.x, mousePos.y,  15);
			ofSetRectMode(OF_RECTMODE_CORNER);			
		}
	}
}

void testApp::renderScreen(int screenIndex) {
	Editable screen = screenSettings[screenIndex];
	if (screen.alpha > 0.0) {
        float masterScreenAlpha = screen.alpha * masterAlpha;
		for (int i=0; i<MAX_LAYERS; i++) {
			Layer layer = screenLayerSettings[screenIndex][i];
			if (layer.alpha > 0.0) {
				// one texture per layer
                Sample sample = samples[layer.selectedSampleIndex];
                if (sample.isVideoPlayer || sample.isVideoGrabber) {
                    
                    if (sample.isPlaying()) {
                        if (sample.isFrameNew()) {
                            cachedTextures[layer.selectedSampleIndex] = sample.getTextureReference();
                        } 
                        // one shader per layer
                        ofEnableAlphaBlending();
                        ofColor selectedColor = colors[layer.selectedColorIndex];					
                        int selectedIndex = screenLayerSettings[screenIndex][i].selectedLayoutIndex;
                        if (selectedIndex == 0) {
                            shader.begin(cachedTextures[layer.selectedSampleIndex].getWidth(), 
                                         cachedTextures[layer.selectedSampleIndex].getHeight(), 
                                         masterScreenAlpha, 
                                         layer.alpha,
                                         layer.contrast,
                                         layer.luminance,
                                         selectedColor.r,
                                         selectedColor.g,
                                         selectedColor.b);
                            cachedTextures[layer.selectedSampleIndex].draw(0, 0, ofGetWidth(), ofGetHeight());		
                            shader.end();
                        } 
                        
                        if (selectedIndex == 1) {
                            float complexity = screenLayerSettings[screenIndex][i].complexity;
                            int nrows = (complexity * 12) + 1;
                            int ncols = nrows;
                            int xSize = ofGetWidth() / nrows;
                            int ySize = ofGetHeight() / ncols;
                            for (int row=0; row<nrows; row++) {
                                for (int col=0; col<ncols; col++) {
                                    shader.begin(cachedTextures[layer.selectedSampleIndex].getWidth(), 
                                                 cachedTextures[layer.selectedSampleIndex].getHeight(), 
                                                 masterScreenAlpha, 
                                                 layer.alpha,
                                                 layer.contrast,
                                                 layer.luminance,
                                                 selectedColor.r,
                                                 selectedColor.g,
                                                 selectedColor.b);                                
                                    int xOffset = row * xSize;
                                    int yOffset = col * ySize;
                                    cachedTextures[layer.selectedSampleIndex].draw(xOffset, yOffset, xSize, ySize);		
                                    shader.end();
                                }
                            }
                        } else {
                            float complexity = screenLayerSettings[screenIndex][i].complexity;
                            ofSetRectMode(OF_RECTMODE_CENTER);
                            for (int k=0; k<MAX_STARS; k++) {
                                TwinklingStar star = stars[k];
                                shader.begin(cachedTextures[layer.selectedSampleIndex].getWidth(), 
                                             cachedTextures[layer.selectedSampleIndex].getHeight(), 
                                             masterScreenAlpha, 
                                             layer.alpha * star.alpha,
                                             layer.contrast,
                                             layer.luminance,
                                             selectedColor.r,
                                             selectedColor.g,
                                             selectedColor.b);
                                cachedTextures[layer.selectedSampleIndex].draw(star.position.x, star.position.y, star.size.x * complexity * 10.0, star.size.y * complexity * 10.0);		
                                shader.end();
                            }
                            ofSetRectMode(OF_RECTMODE_CORNER);
                        }
                        ofDisableAlphaBlending();
                        
                    }
                }
			}
		}
	}
}

void testApp::warpScreen(int screenIndex) {
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
	cvFindHomography(src_mat, dst_mat, translate);
	
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

void testApp::renderWarpTool(int screenNumber) {
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
	
	//for(int i = 0; i < 40; i++)balls[i].draw();
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

void testApp::newMidiMessage(ofxMidiEventArgs& eventArgs) {
	
	// store some data from midi message in variables
	value = eventArgs.byteOne;
	value2 = eventArgs.byteTwo;
	id = eventArgs.channel;
	
	sprintf(msg, "value: (%i,%i), received from port: %i, id: %i \n\nwith %f milliseconds difference from last message",value,value2,port,id,timestamp);
	
	float normValue2 = value2 / 127.0;
	if (id == 1 && value == 7) {
        int newSampleIndex = normValue2 * (MAX_SAMPLES - 1);
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
		int index = normValue2 * (MAX_COLORS - 1);
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
	port = eventArgs.port;
	timestamp = eventArgs.timestamp;
}

void testApp::selectSampleIndex(int newSampleIndex) {
    if (newSampleIndex < MAX_SAMPLES) {
        for (int j=0; j<MAX_SCREENS;j++) {
            if (screenSettings[j].canEdit) {
                for (int i=0; i< MAX_LAYERS; i++) {
                    if (screenLayerSettings[j][i].canEdit) {
                        int oldSampleIndex = screenLayerSettings[j][i].selectedSampleIndex;
                        if (sampleActiveCount[oldSampleIndex] > 0) {
                            sampleActiveCount[oldSampleIndex]--;
                        }
                        screenLayerSettings[j][i].selectedSampleIndex = newSampleIndex;
                        sampleActiveCount[newSampleIndex]++;	
                    }
                }
            }
        }						
    }
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    sprintf(msg, "pressed key %d", key);
    ofLog(OF_LOG_WARNING, msg);
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
        switch(key) {
            case 'q': 
                selectSampleIndex(0);
                break;
            case 'w':
                selectSampleIndex(1);
                break;
            case 'e':
                selectSampleIndex(2);
                break;
            case 'r':
                selectSampleIndex(3);
                break;
            case 't':
                selectSampleIndex(4);
                break;
            case 'y':
                selectSampleIndex(5);
                break;
            case 'u':
                selectSampleIndex(6);
                break;
            case 'i':
                selectSampleIndex(7);
                break;
            case 'o':
                selectSampleIndex(8);
                break;
            case 'p':
                selectSampleIndex(9);
                break;
            case 'a': 
                selectSampleIndex(10);
                break;
            case 's':
                selectSampleIndex(11);
                break;
            case 'd':
                selectSampleIndex(12);
                break;
            case 'f':
                selectSampleIndex(13);
                break;
            case 'g':
                selectSampleIndex(14);
                break;
            case 'h':
                selectSampleIndex(15);
                break;
            case 'j':
                selectSampleIndex(16);
                break;
            case 'k':
                selectSampleIndex(17);
                break;
            case 'l':
                selectSampleIndex(18);
                break;
            case 'z':
                selectSampleIndex(19);
                break;
            case 'x':
                selectSampleIndex(20);
                break;
            case 'c':
                selectSampleIndex(21);
                break;
            case 'v':
                selectSampleIndex(22);
                break;
            case 'b':
                selectSampleIndex(23);
                break;
            case 'n':
                selectSampleIndex(24);
                break;
            case 'm':
                selectSampleIndex(25);
                break;
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	mousePos.x = x;
	mousePos.y = y;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
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
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	
}
