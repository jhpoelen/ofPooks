#include "ofMain.h"
#include "pooksApp.h"
#include "ofAppGlutWindow.h"

int main( ){
  #ifdef TARGET_OPENGLES
  ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
  #endif
  ofSetupOpenGL(1024, 768, OF_WINDOW);
  ofRunApp(new pooksApp());
}
