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
private:
    Uint32  m_flagsSdl;
    Uint32  m_flagsSdlImg;
    
    Uint32 m_gameTime;
    double m_deltaTime;
    
public:
    bool    quit;
    Window  window;
    
    std::vector<std::string>         resToLoad;
    std::map<std::string,Texture*>   textures;
    std::map<std::string,TTF_Font*>  fonts;
    
    std::vector<Script>              scripts;
    
    std::map<SDL_Keycode, bool>      kbState;
    std::map<SDL_Keycode, bool>      kbStateOnceDown;
    std::map<SDL_Keycode, bool>      kbStateOnceUp;
    
    const double &                   deltaTime;
    std::vector<GameObject*>         gameObjects;
    
    // FUNCTIONS-----------------------------------
    
    Engine();
    
    byte    initLibs();
    void    loadResources();
    void    enterMainLoop();
    
private:
    void    calcDeltaTime();
    void    doScripts();
    void    doInput();
    void    doUpdate();
    void    doRender();
};





extern Engine engine;




