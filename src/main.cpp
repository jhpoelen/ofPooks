#include "ofMain.h"
#include "pooksApp.h"
#include "ofAppGlutWindow.h"

int main( ){
    //ofAppGlutWindow window;
	//ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
	ofSetupOpenGL(1024, 768, OF_WINDOW);
  ofRunApp(new pooksApp());
}
