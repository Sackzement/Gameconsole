/*#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
using namespace std;

#include "src/types.h"

#include "src/game_vars.h"







bool    isConsoleOpen = false;

Uint32  gameTime       = 0;
Uint32  delayTime      = 0;
double  delta          = 0.;
const Uint32  fps      = 30;
Uint32  msPerFrame     = 1000 / fps;

vector<SDL_Keycode>  lastKeys  = vector<SDL_Keycode> ();
uint 				 keyToHold = 100;




//---------------------------------------
// functions

void calcDelta() ;
void delay() ;

void inputKeyDown (SDL_KeyboardEvent kb_ev) ;
void printConsoleCmds() ;
void setFullscreen(bool val);


void toLoad()  {
    
    resToLoad.push_back("res/lazy.ttf");
    resToLoad.push_back("res/ululu.png");
}
class a : public Image  {
public:
    a()  {
        texture = textures["res/ululu.png"];
    }
    void input() override  {
    	
        if ( kbState[SDLK_w] )
            pos.y -= 10;
        if ( kbState[SDLK_a] )
            pos.x -= 10;
        if ( kbState[SDLK_s] )
            pos.y += 10;
        if ( kbState[SDLK_d] )
            pos.x += 10;
        
        if ( kbState[SDLK_y] )  {
            
            size.x += .1f;
            size.y += .1f;
        }
        if ( kbState[SDLK_x] )  {
            
            size.x -= .1f;
            size.y -= .1f;
            }
        
        if ( kbState[SDLK_q] )
            angle -= 10;
        if ( kbState[SDLK_e] )
            angle += 10;
    }
    
};
class b : public a  {
public:
    void input() override  {
        
        if ( kbState[SDLK_UP] )
            pos.y -= 10;
        if ( kbState[SDLK_LEFT] )
            pos.x -= 10;
        if ( kbState[SDLK_DOWN] )
            pos.y += 10;
        if ( kbState[SDLK_RIGHT] )
            pos.x += 10;
        
        if ( kbState[SDLK_PERIOD] )  {
            
            size.x += .1f;
            size.y += .1f;
        }
        if ( kbState[SDLK_MINUS] )  {
            
            size.x -= .1f;
            size.y -= .1f;
        }
        if ( kbState[SDLK_k] )
            angle -= 10;
        if ( kbState[SDLK_l] )
            angle += 10;
    }
};
class Level1 : public GameObject  {
public:
    
};
class GameInput : public GameObject  {
public:
    void input() override  {
        
        if ( kbStateOnceDown[SDLK_ESCAPE] )
            quit = true;
    }
};
void  setInputObjects()  {
    
    GameInput* inp = new GameInput();
    gameObjects.push_back(inp);
}
void ululu()  {
    
    a* A = new a();
    b* B = new b();
    A->addChild(B);
    gameObjects.push_back(A);
    
    
    GameObject* g = new GameObject();
    for (int i=0; i<800; ++i)  {
        
        Point* p = new Point();
        p->pos.x = i;
        p->pos.y = 100 + sin(i) * 20;
        p->color = 0xffffffff;
        
        g->addChild(p);
    }
    gameObjects.push_back(g);
    
    Rect* r = new Rect();
    r->color.r = 255;
    r->pos.y = 500;
    r->size.x = 40;
    r->size.y = 40;
    RectFill* rf = new RectFill();
    rf->color.g = 255;
    rf->pos.y = 400;
    rf->size.x = 40;
    rf->size.y = 40;
    gameObjects.push_back(r);
    gameObjects.push_back(rf);
}
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#include <math.h>
int main(int argc, char** argv)
{
    if ( initLibs() )    {
        
        if ( createWindowAndRenderer() )  {
            
            toLoad();
            loadResources();
            setInputObjects();
            ululu();
            gameTime = SDL_GetTicks() ;
        
            // mainloop
            while (quit == false )  {
                
                calcDelta();
                
                doScripts();
                input();
                update();
                delay();
                
                render();
            }
        }
    }
    return 0;
}



//-----------------------------------------------------------------------------------



void  calcDelta()    {
    
    Uint32 lastGameTime ;
    
    lastGameTime  = gameTime ;
    gameTime      = SDL_GetTicks() ;
    
    Uint32 timeDiff = gameTime - lastGameTime ;
    
    delta  = double(timeDiff) / 1000. ;
    
    // show FPS
    /*static Uint32 mytime = 0 ;
    mytime += timeDiff ;
    if ( mytime >= 1000 )    {
        
        cout << "FPS = " << 1000. / double(timeDiff) << endl ;
        mytime = 0 ;
    }*//*
}
void    inputKeyDown (SDL_KeyboardEvent kb_ev)    {
    
    SDL_Keycode key = kb_ev.keysym.sym ;
    
    if ( kb_ev.repeat == 0 )
        switch (key) {
            case SDLK_ESCAPE:
                quit = true ;
                break;
            case SDLK_TAB:
                isConsoleOpen = ! isConsoleOpen ;
                cout << "Console " << (isConsoleOpen? "opened":"closed") << endl ;
                break;
            /*case SDLK_UP:  {
                vector<Sprite>::iterator it = sprites.begin() ;
                for(; it!=sprites.end() ;++it)
                    it->setSize( it->getSize().w +1.f, it->getSize().w +1.f );
            }break;
            case SDLK_DOWN:  {
                vector<Sprite>::iterator it = sprites.begin() ;
                for(; it!=sprites.end() ;++it)
                    it->setSize( it->getSize().w -1.f, it->getSize().w -1.f );
            }break;*//*
        }
    
    if ( isConsoleOpen )    {
        
        bool validInput = false ;
        
        switch (key) {
            case SDLK_RETURN:
            case SDLK_BACKSPACE:
            case SDLK_LEFT:
            case SDLK_RIGHT:
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_SPACE:
                validInput = true ;
                break;
                
            default:
                if ( ( key >= SDLK_a && key <= SDLK_z )
                  || ( key >= SDLK_0 && key <= SDLK_9 ) )
                    validInput = true ;
                break;
        }
        
        if (validInput)
            switch (key)    {
                    
                case SDLK_RETURN:
                {
                    string inputString = "" ;
                    
                    for ( int i=0 ; i<lastKeys.size() ; ++i )
                        inputString += lastKeys[i] ;
                    lastKeys.clear() ;
                    
                    cout << "INPUT: " << inputString << endl ;
                    if ( inputString == "list" )  printConsoleCmds() ;
                    if ( inputString == "set fs on" )   setFullscreen(true) ;
                    if ( inputString == "set fs off" )  setFullscreen(false) ;
                    if ( inputString == "exit" )  quit = true ;
                } break ;
                    
                case SDLK_BACKSPACE:
                {
                    if ( lastKeys.size() > 0 )
                        lastKeys.pop_back() ;
                } break ;
                
                case SDLK_LEFT:
                case SDLK_RIGHT:
                case SDLK_UP:
                case SDLK_DOWN:
                    break ;
                    
                case SDLK_SPACE:
                default:
                {
                    if ( lastKeys.size() < keyToHold )
                        lastKeys.push_back(key) ;
                }
            }
        
    }

}
void    printConsoleCmds()    {
    
    cout << "list" 	 << endl
    	 << "get" 	 << endl
    	 << "set" 	 << endl
         << "set fs on/off" << endl
         << "create" << endl
    	 << "select" << endl
    	 << "exit"   << endl ;
    
}

void    setFullscreen(bool val)    {
    
    Uint32 winFlags = SDL_GetWindowFlags(window) ;
    bool   winFull = winFlags & SDL_WINDOW_FULLSCREEN_DESKTOP ;
    
    if (val != winFull)  {
        
        if (val)
            winFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP ;
        else
            winFlags &= ~SDL_WINDOW_FULLSCREEN_DESKTOP ;
        
        SDL_SetWindowFullscreen(window, winFlags) ;
        cout << "Fullscenn  " << (val? "on":"off") << endl ;
    }
}
void    delay    ()    {
    
    Uint32 currTime  = SDL_GetTicks() ;
    Uint32 timeDiff  = currTime - delayTime ;
    
    if ( timeDiff < msPerFrame )    {
        Uint32 toDelay = msPerFrame - timeDiff ;
        SDL_Delay(toDelay) ;
    }
    
    delayTime  = SDL_GetTicks() ;
}









//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA


/*
 console.addScript("set fs $b", func) ;
 console.addScript("set res $i $i", func) ;
*//*



const SDL_Keycode KEY_CONSOLE_TOGGLE     = SDLK_TAB;
const SDL_Keycode KEY_CONSOLE_INTERPRET  = SDLK_RETURN;

class Console
{
public:
    bool isOpen();
    void open();
    void input(SDL_KeyboardEvent kb_ev);
    void interpretInput();
    void close();
private:
    bool m_open         = false;
    //bool m_keyRepeat    = true;
    
    string inputString  = "" ;
    string::iterator    cursorPos    = inputString.end();
};

bool Console::isOpen()    {
    
    return m_open;
}
void Console::open()    {
    
    m_open = true;
}
void Console::input(SDL_KeyboardEvent kb_ev)    {
    
    if ( kb_ev.repeat == 0 )    {
        // SPECIAL KEYS
        switch (kb_ev.keysym.sym)    {
            
            case KEY_CONSOLE_TOGGLE:
                m_open  = ! m_open;
                break;
            case KEY_CONSOLE_INTERPRET:
                interpretInput();
                break ;
        }
    }
    
    // NORMAL KEYS
    if ( m_open )    {
        
        SDL_Keycode key  = kb_ev.keysym.sym;
        
        // validate key
        bool validInput = false ;
        switch (key) {
            case SDLK_BACKSPACE:
            case SDLK_LEFT:
            case SDLK_RIGHT:
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_SPACE:
                validInput = true ;
                break;
                
            default:
                if ( ( key >= SDLK_a && key <= SDLK_z )
                  || ( key >= SDLK_0 && key <= SDLK_9 ) )
                    validInput = true ;
                break;
        }
        
        // DO STUFF WITH KEY
        if (validInput)
            switch (key)    {
                // special keys
                case SDLK_BACKSPACE:
                {
                    if ( inputString.length() > 0 )
                        inputString.pop_back();
                } break ;
                    
                case SDLK_LEFT:   if( cursorPos != inputString.begin() )    --cursorPos;  break ;
                case SDLK_RIGHT:  if( cursorPos != inputString.end()   )    ++cursorPos;  break ;
                //case SDLK_UP:     if( cursorPos != inputString.end()   )    ++cursorPos;  break ;
                //case SDLK_DOWN:   if( cursorPos != inputString.end()   )    ++cursorPos;  break ;
                    
                //case SDLK_SPACE:
                default:
                {
                    if ( inputString.length() < keyToHold )    {
                        
                        inputString.insert(cursorPos, key) ;
                    }
                }
            }
        
    }
}
void Console::interpretInput()
{
    for ( int i=0 ; i<lastKeys.size() ; ++i )
        inputString += lastKeys[i] ;
    lastKeys.clear() ;
    
    cout << "INPUT: " << inputString << endl ;
    if ( inputString == "list" )  printConsoleCmds() ;
    if ( inputString == "set fs on" )   setFullscreen(true) ;
    if ( inputString == "set fs off" )  setFullscreen(false) ;
    if ( inputString == "exit" )  quit = true ;
}
void Console::close()    {
    
    m_open = false;
}
*/









