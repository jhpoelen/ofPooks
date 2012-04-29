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
    return videoPlayer.loadMovie(name);
}

bool Sample::initGrabber() {
    isVideoPlayer = false;
    isVideoGrabber = true;
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

ofTexture & Sample::getTextureReference() {
    ofTexture textureRef;
    if (isVideoPlayer) {
        return videoPlayer.getTextureReference();
    } else if (isVideoGrabber) {
        return  videoGrabber.getTextureReference();
    }
    // this reference will be invalid after exit of this scope
    return textureRef;
    
}
