//
//  sample.cpp
//  ofPooks
//
//  Created by jorrit poelen on 4/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "sample.h"

Sample::Sample() {
    activeCount = 0;
}

bool Sample::loadMovie(string name) {
    isVideoPlayer = true;
    isVideoGrabber = false;
    return videoPlayer.loadMovie(name);
}

bool Sample::initGrabber() {
    isVideoPlayer = false;
    isVideoGrabber = true;
    videoGrabber.setVerbose(false);
    videoGrabber.setDeviceID(3);
    bool loaded = videoGrabber.initGrabber(320,240,true);
    int grabW = videoGrabber.width;
    int grabH = videoGrabber.height;
    printf("asked for 320 by 240 - actual size is %i by %i", grabW, grabH);
    return loaded;
}

void Sample::setUseTexture(bool bUse) {
    if (isVideoPlayer) {
        videoPlayer.setUseTexture(bUse);
    } else if (isVideoGrabber) {
        videoGrabber.setUseTexture(bUse);
    }
}

bool Sample::loadTextBuffer(string name) {
    isVideoPlayer = false;
    isVideoGrabber = false;
    text = ofBufferFromFile(name);
    bool loaded = font.loadFont("type/frabk.ttf", 80);
    return loaded;
}


void Sample::play() {
    if (isVideoPlayer) {
        videoPlayer.play();
    } else if (isVideoGrabber) {
        grabberActive = true;
    }
}

bool Sample::isPlaying() {
    bool isPlaying = false;
    
    if (isVideoPlayer) {
        isPlaying = videoPlayer.isLoaded() && videoPlayer.isPlaying();
    } else if (isVideoGrabber) {
        isPlaying = grabberInitialized && grabberActive;
    }
    return isPlaying;
}

bool Sample::isFrameNew() {
    bool isFrameNew = true;
    if (isVideoPlayer) {
        isFrameNew = videoPlayer.isFrameNew();
    } else if (isVideoGrabber) {
        isFrameNew = videoGrabber.isFrameNew();
    }
    return isFrameNew;
}

void Sample::stop() {
    if (isVideoPlayer) {
        videoPlayer.stop();
    } else if (isVideoGrabber) {
        grabberActive = false;
    }
}

void Sample::update() {
    if (isVideoPlayer) {
        videoPlayer.update();
    } else if (isVideoGrabber) {
        videoGrabber.update();
    }
}

void Sample::setSpeed(float speed) {
    if (isVideoPlayer) {
        videoPlayer.setSpeed(speed);
    }
}

void Sample::setVolume(float volume) {
    if (isVideoPlayer) {
        videoPlayer.setVolume(volume);
    }
}

void Sample::cacheTextureReference() {
    if (isVideoPlayer) {
        textureReference = videoPlayer.getTextureReference();
    } else if (isVideoGrabber) {
        textureReference = videoGrabber.getTextureReference();
    }
}

ofTexture &Sample::getTextureReference() {
    return textureReference;
}

int Sample::getActiveCount() {
    return activeCount;
}
void Sample::increaseActiveCount() {
    activeCount++;
}
void Sample::decreaseActiveCount() {
    if (activeCount > 0) {
        activeCount--;
    }
}

bool Sample::isLoaded() {
    bool loaded = false;
    if (isVideoPlayer) {
        loaded = videoPlayer.isLoaded();
    } else if (isVideoGrabber) {
        loaded = videoGrabber.isInitialized();
    } else if (!isVideoGrabber && !isVideoPlayer) {
        loaded = font.isLoaded();
    }
    return loaded;
}

