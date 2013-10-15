#pragma once

#include "sample.h"
#include "sampleText.h"
#include "ofMain.h"

class SampleFactory {
  
public:
    vector<Sample*> createSamples();
    vector<Sample*> createSamples(ofDirectory libraryDir);
    
private:
    Sample* createSampleByName(string name);
    
};