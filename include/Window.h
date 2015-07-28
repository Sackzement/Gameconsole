#pragma once
#include <SDL2/SDL_render.h>  // for SDL_Renderer and SDL_Window
#include "types.h"

class Window  {
public:
    bool     create();
    
    void     setTitle (const std::string& s);
    void     setResolution (const int& w, const int& h);
    void     setPosition (const int& x, const int& y);
    void     setFullscreen(bool val);
    std::string     getTitle()          const;
    vec2<int>       getResolution()     const;
    vec2<int>       getPosition()       const;
    
    operator SDL_Window* ();
    operator SDL_Renderer* ();
    
private:
    std::string      m_title          = "";
    vec2<int>        m_position       = vec2<int>(SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    vec2<int>        m_resolution     = vec2<int>(800,600);
    unsigned int     m_flagsWindow    = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL ;
    unsigned int     m_flagsRenderer  = SDL_RENDERER_ACCELERATED ;
    
    SDL_Window*      m_sdlWindow      = nullptr;
    SDL_Renderer*    m_sdlRenderer    = nullptr;
};





