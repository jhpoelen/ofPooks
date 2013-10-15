#pragma once

#include "ofMain.h"

class Sample {
private:
    int activeCount;
    
public:
    Sample();
    
    ofVideoPlayer videoPlayer;
    ofVideoGrabber videoGrabber;
    ofTexture textureReference;
    
    bool isVideoPlayer;
    bool isVideoGrabber;
    bool grabberInitialized;
    bool grabberActive;
    
    virtual bool loadMovie(string name);
    bool initGrabber();
    void setUseTexture(bool bUse);
    
    bool loadTextBuffer(string name);
    
    void play();
    bool isPlaying();
    void stop();
    virtual void update();
    bool isFrameNew();
    void setSpeed(float speed);
    float getSpeed();
    void setVolume(float volume);
    virtual void cacheTextureReference();
    ofTexture &getTextureReference();
    
    int getActiveCount();
    void increaseActiveCount();
    void decreaseActiveCount();
    
    virtual bool isLoaded();
    
};
