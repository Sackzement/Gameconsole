#include "../include/GameObject.h"
#include <algorithm>
#include "../include/Engine.h"







GameObject:: GameObject()
:
pos(0.,0.),
size(1.,1.),
m_children(nullptr)
{}

void GameObject:: input()   {}
void GameObject:: update()  {}
void GameObject:: render()  {}

void GameObject:: renderChildren ()               const  {
    
    if ( hasChildren() )  {
        
        std::vector<GameObject*>::iterator it;
        for (it = m_children->begin(); it != m_children->end(); ++it)  {
            
            vec2<double> posBKP   = (*it)->pos;
            vec2<double> sizeBKP  = (*it)->size;
            
            (*it)->pos   =  this->pos + ((*it)->pos * this->size);
            (*it)->size  *= this->size;
            
            (*it)->render();
            (*it)->renderChildren();
            
            (*it)->pos  = posBKP;
            (*it)->size = sizeBKP;
        }
    }
}
bool GameObject::    hasChildren ()               const  {
    
    if ( m_children == nullptr
      || m_children->empty() )
        return false;
    else
        return true;
}
bool GameObject::       hasChild (GameObject* ch) const  {
    
    if ( m_children != nullptr
     && std::find(m_children->begin(),m_children->end(),ch) != m_children->end() )
        return true;
    else
        return false;
}

void GameObject::    addChild (GameObject* ch)  {
    
    if ( ch )  {
        
        if ( ! m_children )
            m_children = new std::vector<GameObject*>();
            
        if ( ! hasChild(ch) )
            m_children->push_back(ch);
    }
    
}
void GameObject:: removeChild (GameObject* ch)  {
    
    if (ch && m_children)  {
        
        std::vector<GameObject*>::iterator it;
        it  = std::find(m_children->begin(),m_children->end(),ch);
        
        if (it != m_children->end() )  {
            m_children->erase(it);
            
            if ( m_children->empty() )
                delete m_children;
        }
    }
}
void GameObject:: removeAllChildren()  {
    
    delete m_children;
}







Color:: Color() :
   m_color (0),
         r ( *((Uint8*)&m_color) ),
         g ( *(&r+1) ),
         b ( *(&r+2) ),
         a ( *(&r+3) )
{}

Color:: Color(Uint32 newColor) : Color()
{
    m_color = newColor;
}

       Color::  operator Uint32  () const           {
    return m_color;
}
Color& Color::  operator =       (Uint32 newColor)  {
    
    m_color = newColor;
    
    return *this;
}







Shape:: Shape() :
GameObject (),
     color (0xffffffff)
{}






void Rect:: render()  {
    
    SDL_Rect rect = {};
    rect.x = static_cast<int>( pos.x );
    rect.y = static_cast<int>( pos.y );
    rect.w = static_cast<int>( size.x );
    rect.h = static_cast<int>( size.y );
    
    SDL_SetRenderDrawColor(engine.window, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(engine.window, &rect);
}







Texture:: Texture() :
    w (m_w),
    h (m_h),
    m_sdlTexture (nullptr),
    m_w (0),
    m_h (0)
{}
Texture:: Texture( SDL_Texture* sdlTexture, int width, int height ) :
    Texture()
{
    setSdlTexture( sdlTexture, width, height );
}

void Texture:: setSdlTexture( SDL_Texture* sdlTexture, int width, int height )  {
    
    m_sdlTexture = sdlTexture;
    
    m_w  = width;
    m_h  = height;
}
         Texture::  operator SDL_Texture* () {
    
    return m_sdlTexture;
}
Texture& Texture::  operator = (const Texture& tex)  {
    
    this->m_sdlTexture = tex.m_sdlTexture;
    this->m_w = tex.m_w;
    this->m_h = tex.m_h;
    
    return *this;
}







Image::  Image () :
    GameObject (),
    m_clipRect (nullptr),
       texture (),
          flip (0),
           rot (0.)
{}

void Image::  render()  {
    
    SDL_Rect toRect;
    
    toRect.x  = pos.x;
    toRect.y  = pos.y;
    toRect.w  = size.x * (float)texture.w;
    toRect.h  = size.y * (float)texture.h;
    
    SDL_RenderCopyEx( engine.window, texture, m_clipRect, &toRect, rot, NULL, (SDL_RendererFlip)flip );
}
























