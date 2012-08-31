//
//  sample.cpp
//  ofPooks
//
//  Created by jorrit poelen on 4/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "sample.h"

bool Sample::loadMovie(string name) {
    isVideoPlayer = true;
    isVideoGrabber = false;
    activeCount = 0;
    return videoPlayer.loadMovie(name);
}

bool Sample::initGrabber() {
    isVideoPlayer = false;
    isVideoGrabber = true;
    activeCount = 0;
    videoGrabber.setVerbose(false);
    videoGrabber.setDeviceID(3);
    grabberInitialized = videoGrabber.initGrabber(320,240,true);
    int grabW = videoGrabber.width;
    int grabH = videoGrabber.height;
    printf("asked for 320 by 240 - actual size is %i by %i", grabW, grabH);
           
}

void Sample::setUseTexture(bool bUse) {
    if (isVideoPlayer) {
        videoPlayer.setUseTexture(bUse);
    } else if (isVideoGrabber) {
        videoGrabber.setUseTexture(bUse);
    }
}

void Sample::loadTextBuffer(string name) {
    isVideoPlayer = false;
    isVideoGrabber = false;
    activeCount = 0;
    text = ofBufferFromFile(name);
    font.loadFont("type/frabk.ttf", 80);
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
        textureReference = &videoPlayer.getTextureReference();
    } else if (isVideoGrabber) {
        textureReference = &videoGrabber.getTextureReference();
    }
}

ofTexture *Sample::getTextureReference() {
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
