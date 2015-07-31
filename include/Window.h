#pragma once
#include <SDL2/SDL_render.h>  // for SDL_Renderer and SDL_Window
#include "types.h"

class Window  {
public:
    Window();
    
    const std::string &     title;
    const vec2<int> &       pos;
    const vec2<int> &       size;
    const double &          aspectRatio;
    const bool &            fullscreen;
    const unsigned int &    flagsWindow;
    const unsigned int &    flagsRenderer;
    const SDL_DisplayMode & displayMode;
    
    
    
    bool              create ();
    
    void            setTitle (const std::string& newTitle);
    void              setPos (const int& x, const int& y);
    void             setSize (const int& w, const int& h);
    void       setFullscreen (const bool val);
    void      setDisplayMode (const SDL_DisplayMode& newMode);
    void     updateVariables ();
    
    operator    SDL_Window * ();
    operator  SDL_Renderer * ();
    
    
    
private:
    std::string      m_title;
    vec2<int>        m_pos;
    vec2<int>        m_size;
    double           m_aspectRatio;
    bool             m_fullscreen;
    unsigned int     m_flagsWindow;
    unsigned int     m_flagsRenderer;
    
    SDL_Window*      m_sdlWindow;
    SDL_Renderer*    m_sdlRenderer;
    SDL_DisplayMode  m_displayMode;
};





