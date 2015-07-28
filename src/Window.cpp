#include "../include/Window.h"
#include <iostream>



bool  Window::   create()  {
    
    if ( m_sdlWindow )  {
        std::cout << "Error:  Window already created" << std::endl;
        return false;
    }
    else  {
        m_sdlWindow   = SDL_CreateWindow( m_title.c_str(),
                                         m_position.x, m_position.y,
                                         m_resolution.x, m_resolution.y,
                                         m_flagsWindow );
        if ( ! m_sdlWindow )  {
            printf( "Error:  Failed to create window  %s\n", SDL_GetError() );
            return false ;
        }
        else
            m_flagsWindow = SDL_GetWindowFlags(m_sdlWindow);
        
        m_sdlRenderer = SDL_GetRenderer(m_sdlWindow);
        if ( ! m_sdlRenderer )  {
            m_sdlRenderer = SDL_CreateRenderer(m_sdlWindow, -1, m_flagsRenderer);
            if ( ! m_sdlRenderer)  {
                printf( "Error:  Failed to create renderer  %s\n", SDL_GetError() );
                return false ;
            }
        }
        
        return true;
    }
    
}

void  Window::   setTitle (const std::string& s)  {
    
    m_title = s;
}
void  Window::   setResolution (const int& w, const int& h)  {
    
    m_resolution = vec2<int>(w,h);
}
void  Window::   setPosition (const int& x, const int& y)  {
    
    m_position = vec2<int>(x,y);
}
void  Window::   setFullscreen(bool val)  {
    
    if ( val == (m_flagsWindow & SDL_WINDOW_FULLSCREEN_DESKTOP) )
        std::cout << "Window already " << (val?"on":"off") << std::endl;
    else  {
        if (val)
            m_flagsWindow |= SDL_WINDOW_FULLSCREEN_DESKTOP ;
        else
            m_flagsWindow &= ~SDL_WINDOW_FULLSCREEN_DESKTOP ;
        
        if ( m_sdlWindow)  {
            SDL_SetWindowFullscreen(m_sdlWindow, m_flagsWindow) ;
            m_flagsWindow = SDL_GetWindowFlags(m_sdlWindow);
            Uint32 newFullFlag = m_flagsWindow & SDL_WINDOW_FULLSCREEN_DESKTOP;
            if ( val == newFullFlag )
                std::cout << "Set Fullscreen to  " << (val? "on":"off") << std::endl;
            else
                std::cout << "Error:  Couldnt change Fullscreen. curr_val = " << (newFullFlag?"on":"off") << std::endl;
        }
    }
}
std::string  Window::   getTitle()          const  {
    
    return m_title;
}
vec2<int>    Window::   getResolution()     const  {
    
    return m_resolution;
}
vec2<int>    Window::   getPosition()       const  {
    
    return m_position;
}

Window::   operator SDL_Window* ()  {
    return m_sdlWindow;
}
Window::   operator SDL_Renderer* ()  {
    return m_sdlRenderer;
}





