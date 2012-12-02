#pragma once

class KeyboardController {
    
public:
    KeyboardController();
    void keyPressed(int key);
    bool isScreenActive(int screenNumber);
    bool isValidNumber(int screenNumber);
    
private:
    bool screenStatus[6];
    
};