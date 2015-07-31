#include "include/Engine.h"
#include "include/Level1.h"
#include "include/PCinfo.h"

class Player  : public GameObject  {
public:
    double speed = .8;
    
    Player() : GameObject()  {
        pos = vec2<double>(.1,.8);
        size = .1;
        
        Rect* rec = new Rect();
        addChild(rec);
    }
    
    void update() override  {
        
        if (engine.kbState[SDLK_UP])     pos.y  -= speed * engine.deltaTime;
        if (engine.kbState[SDLK_DOWN])   pos.y  += speed * engine.deltaTime;
        if (engine.kbState[SDLK_LEFT])   pos.x  -= speed * engine.deltaTime;
        if (engine.kbState[SDLK_RIGHT])  pos.x  += speed * engine.deltaTime;
    }
    void input()  override  {
        
    }
    
};

Engine engine;
GameObject* screen;
PCinfo* pc;
Level1 * lvl;
Player * pl;

void setWindowDefaultValues()  {
    
    engine.window.setTitle("Jump n Pong");
    engine.window.setSize(2880,1800);
    engine.window.setFullscreen(true);
}


class  MyInput  : public GameObject  {
public:
    void input() override  {
        if (engine.kbStateOnceDown[SDLK_ESCAPE])
            engine.quit = true;
        
        if (engine.kbStateOnceDown[SDLK_SPACE])  {
            
            SDL_DisplayMode largestMode = pc->displays[0].getLargesMode();
            engine.window.setDisplayMode(largestMode);
            
            screen->size   = engine.window.size.y;
            //screen->pos.x  = double(engine.window.size.x - engine.window.size.y) * .5;
            //screen->pos.y  =
            
        }
    }
};



void ululu()  {
    
    screen = new GameObject();
    screen->size   = engine.window.size.y;
    //screen->pos.x  = double(engine.window.size.x - engine.window.size.y) * .5;
    //screen->pos.y  =
    
    
    engine.gameObjects.push_back(screen);
    
    
    MyInput* inp = new MyInput();
    engine.gameObjects.push_back(inp);
    
    lvl = new Level1();
    screen->addChild( lvl );
    
    pl = new Player();
    screen->addChild(pl);
}

void checkCollision()  {
    
    
}

int main (int argc, char** argv)  {
    
    engine.initLibs();
    
    pc = new PCinfo();
    
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