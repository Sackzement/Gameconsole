#pragma  once
#include "game_vars.h"





/////////////////////////////////////
//  DOC
/////  MAIN FILE
//  DEFAULT VALUES
// WINDOW VARs
class Window  {
public:
    bool     create()  {
        
        if ( m_sdlWindow )  {
            std::cout << "Error:  Window already created" << std::endl;
            return false;
        }
        else  {
            m_sdlWindow   = SDL_CreateWindow( m_title.c_str(),
                                        m_position.x, m_position.y,
                                        m_resolution.x, m_resolution.y,
                                        m_flags );
            if ( ! m_sdlWindow )  {
                
                printf( "Error:  Failed to create window  %s\n", SDL_GetError() );
                return false ;
            }
            else  {
                // get flag dif
                Uint32 sdlFlags = SDL_GetWindowFlags(m_sdlWindow);
                if (m_flags != sdlFlags)  {
                    std::cout << "Created window flags are different then specified" << std::endl
                    << "Specified = " << m_flags << "  Created = " << sdlFlags << std::endl;
                    m_flags = sdlFlags;
                }
                
                m_sdlRenderer = SDL_GetRenderer(m_sdlWindow);
                if ( ! windowRenderer )
                    std::cout << "Error:  No window renderer" << std::endl;
                
                return true;
            }
        }

    }
    
    void     setTitle (const std::string& s)  {
    
        m_title = s;
    }
    void     setResolution (const int& w, const int& h)  {
        
        m_resolution = vec2<int>(w,h);
    }
    void     setPosition (const int& x, const int& y)  {
        
        m_position = vec2<int>(x,y);
    }
    void     setFullscreen(bool val)  {
        
        if ( val == (m_flags & SDL_WINDOW_FULLSCREEN_DESKTOP) )
            std::cout << "Window already " << (val?"on":"off") << std::endl;
        else  {
            if (val)
                m_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP ;
            else
                m_flags &= ~SDL_WINDOW_FULLSCREEN_DESKTOP ;
            
            if ( m_sdlWindow)  {
            	SDL_SetWindowFullscreen(m_sdlWindow, m_flags) ;
                m_flags = SDL_GetWindowFlags(m_sdlWindow);
                Uint32 newFullFlag = m_flags & SDL_WINDOW_FULLSCREEN_DESKTOP;
                if ( val == newFullFlag )
            		cout << "Set Fullscreen to  " << (val? "on":"off") << endl;
                else
                    cout << "Error:  Couldnt change Fullscreen. curr_val = " << (newFullFlag?"on":"off") << std::endl;
            }
        }
    }
    std::string     getTitle()          const  {
        
        return m_title;
    }
    vec2<int>       getResolution()     const  {
        
        return m_resolution;
    }
    vec2<int>       getPosition()     const  {
        
        return m_position;
    }
    
    operator SDL_Window* ()  {
        return m_sdlWindow;
    }
    operator SDL_Renderer* ()  {
        return m_sdlRenderer;
    }
    
private:
    std::string      m_title          = "";
    vec2<int>        m_position       = vec2<int>(SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    vec2<int>            m_resolution     = vec2<int>(800,600);
    unsigned int     m_flags          = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL ;
    
    SDL_Window*      m_sdlWindow      = nullptr;
    SDL_Renderer*    m_sdlRenderer    = nullptr;
};




void setWindowDefaultValues(Window& w)  {
    
    w.setTitle("Jump n Pong");
    w.setResolution(2880,1800);
    w.setFullscreen(true);
}
/*int main (int argc, char** argv)  {

    initLibs();
 
    Window win;
    setWindowDefaultValues(win);
    
    // set win data from file
    // if (true)  // if there is a settings file

    // overwrite win data from arguments
	// if (true)  //  if there are arguments
        
    win.create();
    
    loadResources();
    
    //enterMainloop();
        
    
    return 0;
}*/
















