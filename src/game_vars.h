#pragma once
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <map>
using namespace std;


typedef unsigned char byte;


/* USING LIBS *
 SDL2         *
 SDL_image    *
 SDL_ttf      */

// LIB_FLAGs
const Uint32  LIB_FLAG_SDL      = SDL_INIT_EVERYTHING;
const Uint32  LIB_FLAG_SDL_IMG  = IMG_INIT_PNG ;

byte    initLibs()  {
    
    // INIT SDL
    if    ( SDL_Init(LIB_FLAG_SDL) != 0 )  {
        
        printf( "Error:  Failed to init SDL  %s\n", SDL_GetError() );
        return 0;
    }
    
    byte succNum  = 1;
    // INIT SDL_img
    if( IMG_Init(LIB_FLAG_SDL_IMG) == 0 )  {
        
        printf( "Error:  Failed to init SDL_img  %s\n", SDL_GetError() );
        succNum |= 2 ;
    }
    // INIT SDL_ttf
    if   ( TTF_Init() == -1 )  {
        
        printf( "Error:  Failed to init SDL_ttf  %s\n", SDL_GetError() );
        succNum |= 4 ;
    }
    
    return succNum;
}


#include "types.h"

// WINDOW VARs
const char*       WINDOW_TITLE       = "Jump N Pong" ;
const vec<2,int>  WINDOW_POSITION    (100,100);
const vec<2,int>  WINDOW_RESOLUTION  (800,600);
const Uint32      WINDOW_FLAG        = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL ;
// RENDERER FLAGs
const Uint32      RENDERER_FLAG      = SDL_RENDERER_ACCELERATED ;

// FILES TO LOAD
cchar*  FILE_TTF_FONT   = "res/lazy.ttf";
cchar*  FILE_PNG_ULULU  = "res/ululu.png";

// WINDOW & RENDERER
SDL_Window*    window         = nullptr;
SDL_Renderer*  windowRenderer = nullptr;
byte    createWindowAndRenderer()  {
    
    // CREATE WINDOW
    window   = SDL_CreateWindow( WINDOW_TITLE,
                                WINDOW_POSITION.x,   WINDOW_POSITION.y,
                                WINDOW_RESOLUTION.w, WINDOW_RESOLUTION.h,
                                WINDOW_FLAG );
    if ( ! window )  {
        
        printf( "Error:  Failed to create window  %s\n", SDL_GetError() );
        return 0 ;
    }
    
    byte succNum = 1;
    
    windowRenderer = SDL_GetRenderer(window);
    if ( ! windowRenderer )  {
        
        // CREATE GPU RENDERER
        windowRenderer = SDL_CreateRenderer( window, -1, RENDERER_FLAG );
        if ( ! windowRenderer )  {
            
            printf( "Error:  Failed to create window GPU renderer  %s\n", SDL_GetError() );
            
            // CREATE CPU RENDERER
            windowRenderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
            if ( ! windowRenderer )  {
                // FALLBACK TO CPU BLITTING
                printf( "Error:  Failed to create window CPU renderer  %s\n", SDL_GetError() );
                succNum |= 4;
            }
            else  {
                cout << "Falling back to CPU renderer" << endl;
                succNum |= 2;
            }
        }
    }
    
    return succNum ;
}

// KEYBOARD STATE
map<SDL_Scancode, bool> kbState          = map<SDL_Scancode, bool>();
map<SDL_Scancode, bool> kbStateOnceDown  = map<SDL_Scancode, bool>();
map<SDL_Scancode, bool> kbStateOnceUp    = map<SDL_Scancode, bool>();

bool    quit = false;




map<cchar*,SDL_Surface*>  sdlSurfaces    = map<cchar*,SDL_Surface*> ();
map<cchar*,SDL_Texture*>  sdlTextures    = map<cchar*,SDL_Texture*> ();
TTF_Font*                 font           = nullptr ;

byte    loadResources  ()    {
    
    byte succNum = 0 ;
    
    // load IMG file
    SDL_Surface* surf = IMG_Load(FILE_PNG_ULULU);
    if( ! surf )
        printf( "Error:  Failed to load image \"%s\"  %s\n", FILE_PNG_ULULU, SDL_GetError() );
    else  {
        sdlSurfaces[FILE_PNG_ULULU]  = surf;
        succNum |= 1 ;
    }
    
    // load font file
    font = TTF_OpenFont( FILE_TTF_FONT, 28 );
    if( ! font )
        printf( "Error:  Failed to load font \"%s\"  %s\n", FILE_TTF_FONT, SDL_GetError() );
    else  succNum |= 2 ;
    
    return succNum;
}


#include "GameObject.h"
vector<GameObject*>  gameObjects  = vector<GameObject*> ();

void    input()  {
    
    kbStateOnceDown.clear();
    kbStateOnceUp.clear();
    
    for (SDL_Event ev; SDL_PollEvent(&ev) != 0 ;)
        switch (ev.type)  {
                
            case SDL_QUIT:
                quit = true;
                break;
                
            case SDL_KEYDOWN:
                kbStateOnceDown [ev.key.keysym.scancode]  = 1;
                kbState         [ev.key.keysym.scancode]  = 1;
                break;
                
            case SDL_KEYUP:
                kbStateOnceUp [ev.key.keysym.scancode]  = 1;
                kbState       [ev.key.keysym.scancode]  = 0;
                break;
        }
    
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
        (*it)->input();
}
void    update()  {
    
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
        (*it)->update();
}
void    render()  {
    
    SDL_SetRenderDrawColor(windowRenderer, 0,0,0,0);
    SDL_RenderClear(windowRenderer);
    
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
        (*it)->render();
    
    SDL_RenderPresent(windowRenderer);
}











