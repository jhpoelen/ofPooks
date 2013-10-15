#include "sampleFactory.h"

Sample* SampleFactory::createSampleByName(string name) {
    return name.rfind(".txt") == string::npos ? new Sample() : new SampleText() ;
};

vector<Sample*> SampleFactory::createSamples() {
    string libraryPath = ofFilePath::join(ofFilePath::getUserHomeDir(), "Movies/Pooks/");
    ofLog(OF_LOG_NOTICE, "samples loading from [" + libraryPath + "] ...");
    ofDirectory libraryDir(libraryPath);
    vector<Sample*> samples = this->createSamples(libraryDir);
    if (samples.size() > 0) {
        ofLog(OF_LOG_NOTICE, samples.size() + "samples loaded from [" + libraryPath + "].");
    } else {
        ofDirectory defaultSamplesDir(ofToDataPath("", true));
        vector<Sample*> samples = this->createSamples(defaultSamplesDir);
        if (samples.size() > 0) {
            ofLog(OF_LOG_NOTICE, samples.size() + " samples loaded from [" + defaultSamplesDir.path() + "]");
        }
    }
    return samples;
};

vector<Sample*> SampleFactory::createSamples(ofDirectory libraryDir) {
    vector<Sample*> samples;
    if (libraryDir.exists() && libraryDir.isDirectory()) {
        ofLog(OF_LOG_NOTICE, "[" + libraryDir.path() + "] exists and has [" + ofToString(libraryDir.listDir()) + "] files.");
        vector<ofFile> files = libraryDir.getFiles();

        for (vector<ofFile>::iterator it = files.begin(); it!=files.end(); ++it) {
            ofFile file = *it;
            ofLog(OF_LOG_NOTICE, "found file [" + file.path() + "]");
            if (file.isFile()) {
                Sample *sample = createSampleByName(file.path());
                if (sample->loadMovie(file.path())) {
                    ofLog(OF_LOG_NOTICE, "loaded [" + file.path() + "]");
                    samples.push_back(sample);
                } else {
                    delete sample;
                    ofLog(OF_LOG_ERROR, "failed to load [" + file.path() + "]");
                }
            } else {
                ofLog(OF_LOG_NOTICE, "skipping [" + file.path() + "], not a file");
            }
        }
    }
    return samples;
}
