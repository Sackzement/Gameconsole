#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_events.h>
using namespace std;

#include "src/Sprite.h"
#include "src/types.h"




//---------------------------------------
// variables
const Uint32	  sdl_img_flags  = IMG_INIT_PNG ;
const  char*      GAME_NAME      = "Jump N Pong" ;
const   vec<2,int>      resolution      (800,600);
const Uint32      windowFlags    = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL ;
const Uint32      rendererFlags  = SDL_RENDERER_ACCELERATED ;
const char * 	  FONT_FILE      = "16_true_type_fonts/lazy.ttf" ;

map<cchar*,SDL_Texture*>   textures  = map<cchar*,SDL_Texture*> () ;
const char *     PNG_FILE_ULULU  = "res/ululu.png";
vector<Sprite>            sprites = vector<Sprite> () ;


SDL_Window*      window    = nullptr ;
SDL_Renderer*    renderer  = nullptr ;
TTF_Font*        font      = nullptr ;

bool    isConsoleOpen = false ;

bool    quit           = false ;
Uint32  gameTime       = 0 ;
Uint32  delayTime      = 0 ;
double  delta          = 0. ;
const Uint32  fps            = 30 ;
Uint32  msPerFrame     = 1000 / fps ;

vector<SDL_Keycode>  lastKeys  = vector<SDL_Keycode> () ;
uint 				 keyToHold = 100 ;




//---------------------------------------
// functions

byte      initLibs      ();

byte      openWin      ();

byte loadData();
void createSpritesFromAllTextures();

void calcDelta() ;
void input() ;
void update() ;
void delay() ;
void render() ;

void inputKeyDown (SDL_KeyboardEvent kb_ev) ;
void printConsoleCmds() ;
void setFullscreen(bool val);




//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA



int main(int argc, char** argv)
{
    if ( initLibs() )    {
        
        if ( openWin() )    {
            
            loadData();
            createSpritesFromAllTextures();
            gameTime = SDL_GetTicks() ;
            
            // mainloop
            while (quit == false )    {
                
                calcDelta() ;
                input() ;
                update() ;
                delay() ;
                render() ;
            }
        }
    }
    return 0;
}



//-----------------------------------------------------------------------------------



byte    initLibs  ()    {
    
    // INIT SDL
    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 )  {
        
        cout <<SDL_GetError() << endl ;
        return 0;
    }
    
    byte failNum = 1;
    
    // INIT other libs
    if( TTF_Init() == -1 )  {
        
        cout << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError() << endl ;
        failNum |= 2 ;
    }
    if( IMG_Init(sdl_img_flags) == 0 )  {
        
        cout << "SDL_img could not initialize! SDL_img Error: %s\n" << IMG_GetError() << endl ;
        failNum |= 4 ;
    }
    
    return failNum ;
}
byte    loadData  ()    {
    
    byte succNum = 0 ;
    
    if( ( font = TTF_OpenFont( FONT_FILE, 28 ) )  == NULL )
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
    else  succNum |= 1 ;
    
    // load IMG files  into Surfaces*
    
    SDL_Texture* tex = IMG_LoadTexture(renderer, PNG_FILE_ULULU) ;
    if( tex == NULL )
        printf( "Failed to load Image \"%s\"  Error:  %s\n", PNG_FILE_ULULU, TTF_GetError() );
    else
    {
        textures[PNG_FILE_ULULU]  = tex;
        succNum |= 2 ;
    }
    
    
    return succNum;
}
void createSpritesFromAllTextures()  {
    
    map<cchar*,SDL_Texture*>::iterator it = textures.begin();
    for (; it != textures.end() ;++it)  {
        
        Sprite sp(it->second);
        
        sprites.push_back(sp);
    }
}
byte    openWin   ()    {
    
    window   = SDL_CreateWindow( GAME_NAME, 100, 100, resolution.w, resolution.h, windowFlags ) ;
    
    if ( window == nullptr )    {
        cout << SDL_GetError() << endl ;
        return 0 ;
    }
    
    byte succNum = 1;
    
    renderer = SDL_CreateRenderer(window, -1, rendererFlags ) ;
    if ( renderer == nullptr )    {
        cout << SDL_GetError() << endl ;
        succNum |= 2 ;
    }
    else
        SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 ) ;
    
    
    return succNum ;
}

void    calcDelta()    {
    
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
    }*/
}
void    input    ()    {
    SDL_Event ev ;
    
    while ( SDL_PollEvent(&ev) != 0 ) {
        
        switch (ev.type) {
            
            case SDL_QUIT:
                quit = true ;
                break;
            
            case SDL_KEYDOWN:
                inputKeyDown(ev.key) ;
                break;
        }
    }
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
            case SDLK_UP:  {
                vector<Sprite>::iterator it = sprites.begin() ;
                for(; it!=sprites.end() ;++it)
                    it->setSize( it->getSize().w +1.f, it->getSize().w +1.f );
            }break;
            case SDLK_DOWN:  {
                vector<Sprite>::iterator it = sprites.begin() ;
                for(; it!=sprites.end() ;++it)
                    it->setSize( it->getSize().w -1.f, it->getSize().w -1.f );
            }break;
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
void    update   ()    {
    
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
void    render   ()    {
    
    SDL_RenderClear(renderer);
    
    //renderAllSprites
    vector<Sprite>::iterator it = sprites.begin();
    for ( ; it != sprites.end() ; ++it )
        SDL_RenderCopyEx(renderer, it->texture, &it->srcRect, &it->dstRect, it->angle, it->center, it->flip ) ;
    SDL_RenderPresent(renderer) ;
}







//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA


/*
 console.addScript("set fs $b", func) ;
 console.addScript("set res $i $i", func) ;
*/



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
        
        switch (kb_ev.keysym.sym)    {
            
            case KEY_CONSOLE_TOGGLE:
                m_open  = ! m_open;
                break;
            case KEY_CONSOLE_INTERPRET:
                interpretInput();
                break ;
        }
    }
    
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










