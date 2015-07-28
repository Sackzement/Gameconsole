#pragma once
#include <vector>
#include <string>
#include <map>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include "Window.h"
#include "GameObject.h"

typedef void (*Script) ();



/* USING LIBS *
 SDL2         *
 SDL_image    *
 SDL_ttf      */





class Engine {
public:
    // VARIABLES-----------------------------------
    
    bool                   quit             = false;
    
    Window                 window;
    
    std::vector<std::string>         resToLoad        = std::vector<std::string> ();
    std::map<std::string,Texture*>   textures         = std::map<std::string,Texture*> ();
    std::map<std::string,TTF_Font*>  fonts            = std::map<std::string,TTF_Font*> ();
    
    std::vector<Script>         scripts          = std::vector<Script> ();
    
    std::map<SDL_Keycode, bool> kbState          = std::map<SDL_Keycode, bool>();
    std::map<SDL_Keycode, bool> kbStateOnceDown  = std::map<SDL_Keycode, bool>();
    std::map<SDL_Keycode, bool> kbStateOnceUp    = std::map<SDL_Keycode, bool>();
    
    std::vector<GameObject*>    gameObjects      = std::vector<GameObject*> ();
    
    // FUNCTIONS-----------------------------------
    byte    initLibs()       {
        
        // INIT SDL
        if    ( SDL_Init(m_flagsSdl) != 0 )  {
            
            printf( "Error:  Failed to init SDL  %s\n", SDL_GetError() );
            return 0;
        }
        
        byte succNum  = 1;
        // INIT SDL_img
        if( IMG_Init(m_flagsSdlImg) == 0 )  {
            
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
    void    loadResources()  {
        
        for (auto it = resToLoad.begin(); it != resToLoad.end(); ++it)  {
            
            size_t pointPos = (*it).find('.');
            if ( pointPos == -1 )
                std::cout << *it << "  has no file ending \".file\"" << std::endl;
            else  {
                
                std::string fileEnding = (*it).substr(pointPos+1);
                
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
                        SDL_Texture* sdlTex  = SDL_CreateTextureFromSurface(window, surf);
                        if ( ! sdlTex )
                            printf( "Error:  Failed to create Texture from Surface image  \"%s\"  %s\n", (*it).c_str(), SDL_GetError() );
                        else
                            textures[*it] = new Texture(sdlTex, surf->w, surf->h);
                        
                        SDL_FreeSurface(surf);
                    }
                }
                else
                    std::cout << "No matching file ending for  " << fileEnding << std::endl;
            }
        }
        
    }
    void    enterMainLoop()     {
        
        while ( ! quit ) {
            doScripts();
            doInput();
            doUpdate();
            doRender();
        }
    }
    
    void    doScripts()      {
        
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
            (*it)();
        
        scripts.clear();
    }
    void    doInput()        {
        
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
        }
    }
    void    doUpdate()       {
        
        for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)  {
            
            (*it)->update();
        }
    }
    void    doRender()       {
        
        SDL_SetRenderDrawColor(window, 0,0,0,255);
        SDL_RenderClear(window);
        
        for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)  {
            
            (*it)->render(window);
            (*it)->renderChildren(window);
        }
        
        SDL_RenderPresent(window);
    }
    
    
    
    
    
private:
    Uint32                 m_flagsSdl       = SDL_INIT_EVERYTHING;
    Uint32                 m_flagsSdlImg    = IMG_INIT_PNG;
    
    
    
    
};







