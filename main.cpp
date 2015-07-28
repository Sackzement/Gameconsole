#include "include/Engine.h"


void setWindowDefaultValues(Window& w)  {
    
    w.setTitle("Jump n Pong");
    w.setResolution(2880,1800);
    w.setFullscreen(true);
}




int main (int argc, char** argv)  {
 
    Engine eng;
    
    eng.initLibs();
    
    setWindowDefaultValues(eng.window);
 

    // set win data from file
    // if (true)  // if there is a settings file
 
    // overwrite win data from arguments
	// if (true)  //  if there are arguments
 
    eng.window.create();

    eng.loadResources();
    
    GameObject* screen = new GameObject();
    screen->size       = vec2<double>(2880.,1800.);
    
    RectFill* rec = new RectFill();
    rec->size     = vec2<double>(.1,.1);
    rec->color    = 0xff0000ff;
    
    screen->addChild(rec);
    eng.gameObjects.push_back(screen);
    
    eng.enterMainLoop();
 
    return 0;
 }