#pragma once 

#include "sample.h"
#include "ofMain.h"

class SampleText : public Sample {

public:
    virtual bool loadMovie(string name);
    virtual bool isLoaded();
    virtual void update();
    
private:
    ofBuffer buffer;
    ofTrueTypeFont font;
    
};