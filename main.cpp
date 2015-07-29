#include "include/Engine.h"

Engine engine;

void setWindowDefaultValues()  {
    
    engine.window.setTitle("Jump n Pong");
    engine.window.setResolution(2880,1800);
    engine.window.setFullscreen(true);
}


class  MyInput  : public GameObject  {
public:
    void input() override  {
        if (engine.kbStateOnceDown[SDLK_ESCAPE])
            engine.quit = true;
    }
};

class Player  : public GameObject  {
public:
    double speed = .2;
    
    void update() override  {
        
        if (engine.kbState[SDLK_UP])  pos.y += speed * engine.deltaTime;
    }
    void input()  override  {
        
    }
    
};

void ululu()  {
    
    GameObject* screen = new GameObject();
    screen->size       = vec2<double>(2880.,1800.);
    
    Rect* rec = new Rect();
    rec->size     = vec2<double>(.1,.1);
    rec->color    = 0xff0000ff;
    
    screen->addChild(rec);
    engine.gameObjects.push_back(screen);
    
    
    MyInput* inp = new MyInput();
    engine.gameObjects.push_back(inp);
}

int main (int argc, char** argv)  {
    
    engine.initLibs();
    
    setWindowDefaultValues();
 

    // set win data from file
    // if (true)  // if there is a settings file
 
    // overwrite win data from arguments
	// if (true)  //  if there are arguments
 
    engine.window.create();

    engine.loadResources();
    
    ululu();
    
    engine.enterMainLoop();
 
    return 0;
 }