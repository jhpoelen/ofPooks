//
//  sample.h
//  ofPooks
//
//  Created by jorrit poelen on 4/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ofMain.h"

class Sample {
public:
    ofVideoPlayer videoPlayer;
    ofVideoGrabber videoGrabber;
    ofBuffer text;
    ofTrueTypeFont font;
    
    bool isVideoPlayer;
    bool isVideoGrabber;
    bool grabberInitialized;
    bool grabberActive;
    
    bool loadMovie(string name);
    bool initGrabber();
    void setUseTexture(bool bUse);
    
    void loadTextBuffer(string name);
    
    void play();
    bool isPlaying();
    void stop();
    void update();
    bool isFrameNew();
    void setSpeed(float speed);
    ofTexture & getTextureReference();
    
};
