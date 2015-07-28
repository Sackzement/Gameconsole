#pragma once
#include <iostream>
#include "types.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>




class GameObject  {
public:
    vec2<double>                 pos;
    vec2<double>                 size;
    
    GameObject();
    GameObject copy() const;
    virtual void input()  const;
    virtual void update() const;
    virtual void render( SDL_Renderer* rend ) const;
    
    void renderChildren(SDL_Renderer* rend) const;
    bool hasChildren() const;
    bool hasChild(GameObject* ch) const;
    void addChild(GameObject* ch);
    void removeChild(GameObject* ch);
    void removeAllChildren();
protected:
    std::vector<GameObject*> * m_children;
    
};



struct Color  {
    operator Uint32 ()  {
        return m_color;
    }
    Color& operator= (Uint32 rhs)  {
        
        m_color = rhs;
        
        return *this;
    }
    
    Uint8& r  = *( (Uint8*)&m_color );
    Uint8& g  = *(&r+1);
    Uint8& b  = *(&r+2);
    Uint8& a  = *(&r+3);
private:
    Uint32 m_color = 0;
};


class Shape : public GameObject  {
public:
    Color      color;
};

/*class Point        : public Shape  {
public:
    void render(SDL_Renderer* rend) override  {
        
        SDL_SetRenderDrawColor(windowRenderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(windowRenderer, pos.x, pos.y);
    }
};
class Line         : public Shape  {
public:
    vec2<float> pos2;
    
    void render(SDL_Renderer* rend) override  {
        
        SDL_SetRenderDrawColor(windowRenderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(windowRenderer, pos.x, pos.y, pos2.x, pos2.y);
    }
};
class Rect         : public Shape  {
public:
    void render(SDL_Renderer* rend) const override  {
        
        SDL_Rect rect = {static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x), static_cast<int>(size.y)};
        SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(rend, &rect);
    }
};*/
class RectFill     : public Shape   {
public:
    void render( SDL_Renderer* rend ) const override;
};


class Texture  {
public:
    Texture()  {}
    Texture( SDL_Texture* sdlTexture, int width, int height )  {
        
        setSdlTexture( sdlTexture, width, height );
    }
    void setSdlTexture( SDL_Texture* sdlTexture, int width, int height )  {
        
        m_sdlTexture = sdlTexture;
        
        m_w  = width;
        m_h  = height;
    }
    operator SDL_Texture* () {
        return m_sdlTexture;
    }
    Texture& operator = (const Texture& tex)  {
        
        this->m_sdlTexture = tex.m_sdlTexture;
        this->m_w = tex.m_w;
        this->m_h = tex.m_h;
        
        return *this;
    }
    Texture& operator = (const Texture* tex)  {
        
        return this->operator=(*tex);
    }
    
    const int& w  = m_w;
    const int& h  = m_h;

private:
    SDL_Texture*  m_sdlTexture  = nullptr;
    
    int  m_w  = 0;
    int  m_h  = 0;
};
class Image        : public GameObject  {
private:
    SDL_Rect*  m_clipRect  = nullptr;
public:
    Texture     texture;
    byte       flip        = 0.;
    double     rot         = 0.;
    
    void render( SDL_Renderer* rend ) const override  {
        
        SDL_Rect toRect;
        
        toRect.x  = pos.x;
        toRect.y  = pos.y;
        toRect.w  = size.x * (float)texture.w;
        toRect.h  = size.y * (float)texture.h;
        
        //SDL_RenderCopyEx(<#SDL_Renderer *renderer#>, <#SDL_Texture *texture#>, <#const SDL_Rect *srcrect#>, <#const SDL_Rect *dstrect#>, <#const double angle#>, <#const SDL_Point *center#>, <#const SDL_RendererFlip flip#>)
//        SDL_RenderCopyEx( rend, texture, m_clipRect, &toRect, rot, NULL, (SDL_RendererFlip)flip );
        SDL_RenderCopyEx( rend, nullptr, m_clipRect, nullptr, rot, nullptr, (SDL_RendererFlip)flip );
    }
};












































