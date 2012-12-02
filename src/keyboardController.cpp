#include "keyboardController.h"

KeyboardController::KeyboardController() {
    for (int i=0; i<6; i++) {
        screenStatus[i] = false;
    }
}

bool KeyboardController::isScreenActive(int screenNumber) {
    return isValidNumber(screenNumber) ? screenStatus[screenNumber] : false;
}

bool KeyboardController::isValidNumber(int screenNumber) {
    return screenNumber >= 0 && screenNumber < 6;
}

void KeyboardController::keyPressed(int key) {
    int screenNumber = -1;
    switch (key) {
        case '!':
            screenNumber = 0;
            break;
        case '@':
            screenNumber = 1;
            break;
        case '#':
            screenNumber = 2;
            break;
        case '$':
            screenNumber = 3;
            break;
        case '%':
            screenNumber = 4;
            break;
        case '^':
            screenNumber = 5;
            break;
            
        default:
            break;
    }
    if (isValidNumber(screenNumber)) {
        screenStatus[screenNumber] = !screenStatus[screenNumber];
    }
}

