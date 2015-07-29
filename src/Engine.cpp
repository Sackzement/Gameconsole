#include "../include/Engine.h"







Engine:: Engine() :

   m_flagsSdl (SDL_INIT_EVERYTHING),
m_flagsSdlImg (IMG_INIT_PNG),

m_gameTime(0),
m_deltaTime(0.),

  quit (false),
window (),

resToLoad (),
 textures (),
    fonts (),

  scripts (),

        kbState (),
kbStateOnceDown (),
  kbStateOnceUp (),

deltaTime(m_deltaTime),
gameObjects ()
{}

byte    Engine:: initLibs()       {
    
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
void    Engine:: loadResources()  {
        
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
void    Engine:: enterMainLoop()  {
    
    calcDeltaTime();
    
    while ( ! quit ) {
        doScripts();
        doInput();
        doUpdate();
        doRender();
    }
}

void    Engine:: capGtimeCalcDt()  {
    
    Uint32 lastGameTime = m_gameTime;
    m_gameTime = SDL_GetTicks();
}
void    Engine:: doScripts()      {
        
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
            (*it)();
        
        scripts.clear();
    }
void    Engine:: doInput()        {
        
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
void    Engine:: doUpdate()       {
        
        for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)  {
            
            (*it)->update();
        }
    }
void    Engine:: doRender()       {
        
        SDL_SetRenderDrawColor(window, 0,0,0,255);
        SDL_RenderClear(window);
        
        for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)  {
            
            (*it)->render();
            (*it)->renderChildren();
        }
        
        SDL_RenderPresent(window);
    }
    
    
    

    





