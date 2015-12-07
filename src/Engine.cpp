#include "../include/Engine.h"







Engine:: Engine() :

   m_flagsSdl (SDL_INIT_EVERYTHING),
m_flagsSdlImg (IMG_INIT_PNG),

m_gameTime(0),
m_deltaTime(0.),
m_fps(60),
m_msPerFrame(1000./(double)m_fps),
m_delayTime(0),

  quit (false),
window (),

resToLoad (),
 textures (),
    fonts (),

  scripts (),

        kbState (),
kbStateOnceDown (),
  kbStateOnceUp (),

 gameTime (m_gameTime),
deltaTime (m_deltaTime),
      fps (m_fps),

collChecks (),

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
                    
					TTF_Font* font = TTF_OpenFont((*it).c_str(), 28);
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
    
    doCapGtimeCalcDt();
    m_delayTime = gameTime;
    
    while ( ! quit ) {
        doCapGtimeCalcDt();
        doScripts();
        doInput();
        doUpdate();
        doCollision();
        doDelay();
        doRender();
    }
}
void    Engine:: setFPS(const Uint16& newFPS)  {
    
    m_fps = newFPS;
    m_msPerFrame = 1000. / double(m_fps);
}

void    Engine:: doCapGtimeCalcDt() {
    
    Uint32 lastGameTime = m_gameTime;
    m_gameTime = SDL_GetTicks();
    
    
    m_deltaTime = .001 * static_cast<double>(m_gameTime - lastGameTime);
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
                    if ( ev.key.repeat == 0 )
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
void    Engine:: doUpdate()       {
        
        for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)  {
            
            (*it)->update();
            (*it)->updateChildren();
        }
}
void    Engine:: doCollision()      {
    
	for (auto it = collChecks.begin(); it != collChecks.end(); ++it) {
		(*it)();
	}
}
void    Engine:: doDelay()        {
    
    Uint32 oldDelayTime = m_delayTime;
    m_delayTime = SDL_GetTicks();
    
    Uint32 diff = m_delayTime - oldDelayTime;
    
    if ( double(diff) < m_msPerFrame )  {
        
		Uint32 toWait = Uint32( m_msPerFrame - double(diff) );
        SDL_Delay(toWait);
    }
    
    m_delayTime = SDL_GetTicks();
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
    
    
    

    





