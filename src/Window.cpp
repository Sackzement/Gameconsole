#include "../include/Window.h"
#include <iostream>


Window::  Window() :

        title (m_title),
          pos (m_pos),
         size (m_size),
  aspectRatio (m_aspectRatio),
   fullscreen (m_fullscreen),
  flagsWindow (m_flagsWindow),
flagsRenderer (m_flagsRenderer),
  displayMode (m_displayMode),

        m_title (""),
          m_pos (SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED),
         m_size (800,600),
  m_aspectRatio ( (double)size.x/(double)size.y ),
   m_fullscreen (false),
  m_flagsWindow (SDL_WINDOW_OPENGL),
m_flagsRenderer (SDL_RENDERER_ACCELERATED),

  m_sdlWindow (nullptr),
m_sdlRenderer (nullptr),
m_displayMode()

{}



bool  Window::            create ()  {
    
    if ( m_sdlWindow )  {
        std::cout << "Error:  Window already created" << std::endl;
        return false;
    }
    else  {
        
        m_sdlWindow   = SDL_CreateWindow( title.c_str(),
                                         pos.x, pos.y,
                                         size.x, size.y,
                                         flagsWindow );
        if ( ! m_sdlWindow )  {
            printf( "Error:  Failed to create window  %s\n", SDL_GetError() );
            return false ;
        }
        else  {
            if (displayMode.w > 0)
                setDisplayMode(displayMode);
            else
                updateVariables();
            
            m_sdlRenderer = SDL_GetRenderer(m_sdlWindow);
            if ( ! m_sdlRenderer )  {
                m_sdlRenderer = SDL_CreateRenderer(m_sdlWindow, -1, m_flagsRenderer);
                if ( ! m_sdlRenderer)  {
                    printf( "Error:  Failed to create renderer  %s\n", SDL_GetError() );
                    return false ;
                }
                else
                    return true;
            }
            else
                return true;
        }
    }
    
}

void  Window::          setTitle (const std::string& newTitle)  {
    
    if (m_sdlWindow)  {
        SDL_SetWindowTitle( m_sdlWindow, newTitle.c_str() );
        updateVariables();
    }
    else
        m_title = newTitle;
        
}
void  Window::            setPos (const int& x, const int& y)  {
    
    if (m_sdlWindow)  {
        SDL_SetWindowPosition(m_sdlWindow, x, y);
        updateVariables();
    }
    else
        m_pos = vec2<int>(x,y);
}
void  Window::           setSize (const int& w, const int& h)  {
    
    if (m_sdlWindow)  {
        if (fullscreen)  {
            setFullscreen(false);
            SDL_SetWindowSize(m_sdlWindow, w, h);
            setFullscreen(true);
        }
        else  {
            SDL_SetWindowSize(m_sdlWindow, w, h);
            updateVariables();
        }
    }
    else  {
        m_size = vec2<int>(w,h);
        m_aspectRatio = (double)size.x/(double)size.y;
    }
}
void  Window::     setFullscreen (bool val)  {
    
    if (m_sdlWindow)  {
        
        if (val)
            SDL_SetWindowFullscreen(m_sdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
        else
            SDL_SetWindowFullscreen(m_sdlWindow, 0);
        
        updateVariables();
    }
    else  {
        m_fullscreen = val;
        
        if (val)
            m_flagsWindow |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        else
            m_flagsWindow &= ~SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    
}
void  Window::   updateVariables ()  {
    
    if (m_sdlWindow)  {
        
        m_title = SDL_GetWindowTitle(m_sdlWindow);
        SDL_GetWindowPosition(m_sdlWindow, &m_pos.x, &m_pos.y);
        SDL_GetWindowSize(m_sdlWindow, &m_size.x, &m_size.y);
        m_aspectRatio = (double)size.x/(double)size.y;
        m_flagsWindow  = SDL_GetWindowFlags(m_sdlWindow);
        m_fullscreen   = flagsWindow & SDL_WINDOW_FULLSCREEN_DESKTOP;
        SDL_GetWindowDisplayMode(m_sdlWindow, &m_displayMode);
    }
}

void Window::     setDisplayMode (const SDL_DisplayMode& newMode)  {
    
    if (m_sdlWindow)  {
        if (fullscreen)  {
            setFullscreen(false);
            SDL_SetWindowDisplayMode(m_sdlWindow, &newMode);
            setFullscreen(true);
        }
        else  {
            SDL_SetWindowDisplayMode(m_sdlWindow, &newMode);
            updateVariables();
        }
    }
    else  {
        m_displayMode = newMode;
        m_size = vec2<int>(displayMode.w,displayMode.h);
        m_aspectRatio = (double)size.x/(double)size.y;
    }
}

Window::   operator   SDL_Window * ()  {
    return m_sdlWindow;
}
Window::   operator SDL_Renderer * ()  {
    return m_sdlRenderer;
}





