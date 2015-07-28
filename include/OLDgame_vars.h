#pragma once
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <map>
#include <iostream>
using namespace std;

#include "types.h"




bool    quit = false;


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



// WINDOW VARs
const char*       WINDOW_TITLE       = "Jump N Pong" ;
const vec2<int>  WINDOW_POSITION    (100,100);
const vec2<int>  WINDOW_RESOLUTION  (800,600);
const Uint32      WINDOW_FLAG        = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL ;
// RENDERER FLAGs
const Uint32      RENDERER_FLAG      = SDL_RENDERER_ACCELERATED ;

// WINDOW & RENDERER
SDL_Window*    window         = nullptr;
SDL_Renderer*  windowRenderer = nullptr;
byte    createWindowAndRenderer()  {
    
    // CREATE WINDOW
    window   = SDL_CreateWindow( WINDOW_TITLE,
                                WINDOW_POSITION.x,   WINDOW_POSITION.y,
                                WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y,
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

// SCRIPT
vector<void(*)()> scripts = vector<void(*)()> ();

// INPUT KEYBOARD STATE
map<SDL_Keycode, bool> kbState          = map<SDL_Keycode, bool>();
map<SDL_Keycode, bool> kbStateOnceDown  = map<SDL_Keycode, bool>();
map<SDL_Keycode, bool> kbStateOnceUp    = map<SDL_Keycode, bool>();


#include "GameObject.h"
// RENDER
map<string,Texture*>  textures  = map<string,Texture*> ();
map<string,TTF_Font*> fonts     = map<string,TTF_Font*> ();

vector<string> resToLoad = vector<string> ();

void    loadResources()    {
    
    for (auto it = resToLoad.begin(); it != resToLoad.end(); ++it)  {
        
        size_t pointPos = (*it).find('.');
        if ( pointPos == -1 )
            cout << *it << "  has no file ending \".file\"" << endl;
        else  {

            string fileEnding = (*it).substr(pointPos+1);
            
            if        ( fileEnding == "ttf" )  {
             
                TTF_Font* font = TTF_OpenFont( (*it).c_str(), 28 );
                if( ! font )
                    printf( "Error:  Failed to load font \"%s\"  %s\n", (*it).c_str(), SDL_GetError() );
                else
                    fonts[*it] = font;
            }
            else if ( ( fileEnding == "png" )
                   || ( fileEnding == "jpg" ) )  {
                
                SDL_Surface* surf = IMG_Load( (*it).c_str() );
                if( ! surf )
                    printf( "Error:  Failed to load image \"%s\"  %s\n", (*it).c_str(), SDL_GetError() );
                else  {
                    SDL_Texture* sdlTex  = SDL_CreateTextureFromSurface(windowRenderer, surf);
                    if ( ! sdlTex )
                        printf( "Error:  Failed to create Texture from Surface image  \"%s\"  %s\n", (*it).c_str(), SDL_GetError() );
                    else
                        textures[*it] = new Texture(sdlTex, surf->w, surf->h);
                    
                    SDL_FreeSurface(surf);
                }
            }
            else
                cout << "No matching file ending for  " << fileEnding << endl;
        }
    }
    
}


vector<GameObject*>  gameObjects  = vector<GameObject*> ();

void    doScripts()  {
    
    for (auto it = scripts.begin(); it != scripts.end(); ++it)
        (*it)();
    
    scripts.clear();
}
void    input()  {
    
    kbStateOnceDown.clear();
    kbStateOnceUp.clear();
    
    for (SDL_Event ev; SDL_PollEvent(&ev) != 0 ;)
        switch (ev.type)  {
                
            case SDL_QUIT:
                quit = true;
                break;
                
            case SDL_KEYDOWN:
                kbStateOnceDown [ev.key.keysym.sym]  = 1;
                kbState         [ev.key.keysym.sym]  = 1;
                break;
                
            case SDL_KEYUP:
                kbStateOnceUp [ev.key.keysym.sym]  = 1;
                kbState       [ev.key.keysym.sym]  = 0;
                break;
        }
    
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)  {
        
        (*it)->input();
        (*it)->inputChildren();
    }
}
void    update()  {
    
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)  {
        
        (*it)->update();
        (*it)->updateChildren();
    }
}
void    render()  {
    
    SDL_SetRenderDrawColor(windowRenderer, 0,0,0,0);
    SDL_RenderClear(windowRenderer);
    
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)  {
        
        (*it)->render();
        (*it)->renderChildren();
    }
    
    SDL_RenderPresent(windowRenderer);
}











