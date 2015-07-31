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
    Uint16 m_fps;
    double m_msPerFrame;
    Uint32 m_delayTime;
    
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
    
    const Uint32 &                   gameTime;
    const double &                   deltaTime;
    const Uint16 &                   fps;
    
    std::vector<GameObject*>         gameObjects;
    
    // FUNCTIONS-----------------------------------
    
    Engine();
    
    byte    initLibs();
    void    loadResources();
    void    enterMainLoop();
    void    setFPS(const Uint16& newFPS);
    
private:
    void    capGtimeCalcDt();
    void    doScripts();
    void    doInput();
    void    doUpdate();
    void    delay();
    void    doRender();
};





extern Engine engine;




