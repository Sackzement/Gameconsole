#pragma once
//#include <vector>
//#include <SDL2/SDL_stdinc.h>
#include "game_vars.h"


class GameObject  {
public:
    virtual void input()   {}
    virtual void update()  {}
    virtual void render()  {}
};
class Group        : public GameObject  {
public:
    vector<GameObject*> childObjects = vector<GameObject*>();
    
    void input()  override  {
        
        for (auto it = childObjects.begin(); it != childObjects.end(); ++it)
            (*it)->input();
            }
    void update() override  {
        
        for (auto it = childObjects.begin(); it != childObjects.end(); ++it)
            (*it)->update();
            }
    void render() override  {
        
        for (auto it = childObjects.begin(); it != childObjects.end(); ++it)
            (*it)->render();
            }
};

struct Color  {
    operator Uint32 ()  {
        return m_color;
    }
    void  operator= (Uint32 rhs)  {
        
        m_color = rhs;
    }
    
    Uint8& r  = *( (Uint8*)&m_color );
    Uint8& g  = *(&r+1);
    Uint8& b  = *(&r+2);
    Uint8& a  = *(&r+3);
private:
    Uint32 m_color = 0;
};

class Point        : public GameObject  {
public:
    int x  = 0;
    int y  = 0;
    
    Color color;
    
    void render() override  {
        
        SDL_SetRenderDrawColor(windowRenderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(windowRenderer, x, y);
    }
};
class Line         : public GameObject  {
public:
    int x   = 0;
    int y   = 0;
    int x2  = 0;
    int y2  = 0;
    
    Color color;
    
    void render() override  {
        
        SDL_SetRenderDrawColor(windowRenderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(windowRenderer, x, y, x2, y2);
    }
};
class Rect         : public GameObject  {
public:
    SDL_Rect rect = {0,0,4,4};
    
    Color color;
    
    void render() override  {
        
        SDL_SetRenderDrawColor(windowRenderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(windowRenderer, &rect);
    }
};
class RectFill     : public GameObject  {
public:
    SDL_Rect rect = {0,0,4,4};
    
    Color color;
    
    void render() override  {
        
        SDL_SetRenderDrawColor(windowRenderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(windowRenderer, &rect);
    }
};
class PixelChanger : public GameObject  {
public:
    void input()  override  {
        
        if ( kbStateOnceDown[SDL_SCANCODE_SPACE] )
            printf("space pressed\n");
            
        if ( kbStateOnceDown[SDL_SCANCODE_R] )
            printf("RAM = %i\n", SDL_GetSystemRAM() );
    }
};




