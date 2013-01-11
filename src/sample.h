//
//  sample.h
//  ofPooks
//
//  Created by jorrit poelen on 4/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ofMain.h"

class Sample {
private:
    int activeCount;
    
public:
    Sample();
    
    ofVideoPlayer videoPlayer;
    ofVideoGrabber videoGrabber;
    ofBuffer text;
    ofTrueTypeFont font;
    ofTexture textureReference;
    
    bool isVideoPlayer;
    bool isVideoGrabber;
    bool grabberInitialized;
    bool grabberActive;
    
    bool loadMovie(string name);
    bool initGrabber();
    void setUseTexture(bool bUse);
    
    bool loadTextBuffer(string name);
    
    void play();
    bool isPlaying();
    void stop();
    void update();
    bool isFrameNew();
    void setSpeed(float speed);
    float getSpeed();
    void setVolume(float volume);
    void cacheTextureReference();
    ofTexture &getTextureReference();
    
    int getActiveCount();
    void increaseActiveCount();
    void decreaseActiveCount();
    
    bool isLoaded();
    
};
