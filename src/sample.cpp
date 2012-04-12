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
    return videoPlayer.loadMovie(name);
}

void Sample::setUseTexture(bool bUse) {
    videoPlayer.setUseTexture(bUse);
}

void Sample::loadTextBuffer(string name) {
    isVideoPlayer = false;
    text = ofBufferFromFile(name);
    font.loadFont("type/frabk.ttf", 80);
}


void Sample::play() {
    if (isVideoPlayer) {
        videoPlayer.play();
    }
}

bool Sample::isPlaying() {
    bool isPlaying = true;
    if (isVideoPlayer) {
        isPlaying = videoPlayer.isPlaying();
    }
    return isPlaying;
}

void Sample::stop() {
    if (isVideoPlayer) {
        videoPlayer.stop();
    }
}

void Sample::update() {
    if (isVideoPlayer) {
        videoPlayer.update();
    }
}

void Sample::setSpeed(float speed) {
    if (isVideoPlayer) {
        videoPlayer.setSpeed(speed);
    }
}
