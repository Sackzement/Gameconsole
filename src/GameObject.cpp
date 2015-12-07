#include "../include/GameObject.h"
#include <algorithm>
#include "../include/Engine.h"







GameObject:: GameObject() :

pos(0.),
size(1.),

m_parent(NULL),
m_children(NULL)
{}



void GameObject:: input()   {}
void GameObject:: update()  {}
void GameObject:: render()  {}

bool GameObject:: hasParent() const  {
    
    if (m_parent)
        return true;
    else
        return false;
}
GameObject * GameObject:: getParent() const  {
    
    return m_parent;
}
void GameObject:: addParent(GameObject* newParent)  {
    
    if (newParent  &&  newParent != m_parent)  {
        
        if (m_parent) {
            GameObject * oldParent = m_parent;
            m_parent = NULL;
            
            oldParent->removeChild(this);
        }
    
        m_parent = newParent;
        m_parent->addChild(this);
    }
}

void GameObject:: removeParent()  {
    
    if (m_parent)  {
        GameObject* oldParent = m_parent;
        m_parent = NULL;
        
        oldParent->removeChild(this);
    }
}


bool GameObject::    hasChildren ()               const  {
    
    if ( m_children == NULL
        || m_children->empty() )
        return false;
    else
        return true;
}
std::vector<GameObject*> * GameObject::  getChildren() const  {
    
    return m_children;
}
bool GameObject::       hasChild (GameObject* ch) const  {
    
    if ( m_children != NULL
        && std::find(m_children->begin(),m_children->end(),ch) != m_children->end() )
        return true;
    else
        return false;
}
void GameObject::  inputChildren ()               const  {
    
    if ( hasChildren() )  {
        
        std::vector<GameObject*>::iterator it;
        for (it = m_children->begin(); it != m_children->end(); ++it)  {
            
            (*it)->input();
            (*it)->inputChildren();
        }
    }
}
void GameObject:: updateChildren ()               const  {
    
    if ( hasChildren() )  {
        
        std::vector<GameObject*>::iterator it;
        for (it = m_children->begin(); it != m_children->end(); ++it)  {
            
            (*it)->update();
            (*it)->updateChildren();
        }
    }
}
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

void GameObject::    addChild (GameObject* ch)  {
    
    if ( ch )  {
        
        if ( ! m_children )
            m_children = new std::vector<GameObject*>();
            
        if ( ! hasChild(ch) )  {
            m_children->push_back(ch);
            ch->addParent(this);
        }
    }
    
}
void GameObject:: removeChild (GameObject* ch)  {
    
    if (ch && m_children)  {
        
        std::vector<GameObject*>::iterator it;
        it  = std::find(m_children->begin(),m_children->end(),ch);
        
        if (it != m_children->end() )  {
            GameObject* oldChild = *it;
            m_children->erase(it);
            oldChild->removeParent();
            
            if ( m_children->empty() )
                delete m_children;
        }
    }
}
void GameObject:: removeAllChildren ()  {
    
    delete m_children;
}

bool GameObject:: checkColl (const GameObject & otherGO, vec2<double> & inters) const  {
    
    double thisRight  = pos.x + size.x;
    double thisBottom = pos.y + size.y;
    
    double otherRight  = otherGO.pos.x + otherGO.size.x;
    double otherBottom = otherGO.pos.y + otherGO.size.y;
    
    if ( (pos.x < otherRight  && thisRight >  otherGO.pos.x)
      && (pos.y < otherBottom && thisBottom > otherGO.pos.y) )  {
        
        
        double Amin, Amax, Bmin, Bmax;
        
        /* Horizontal intersection */
        Amin = pos.x;
        Amax = Amin + size.x;
        Bmin = otherGO.pos.x;
        Bmax = Bmin + otherGO.size.x;
        if (Bmin > Amin)
            Amin = Bmin;
        if (Bmax < Amax)
            Amax = Bmax;
        inters.x = Amax - Amin;
        
        /* Vertical intersection */
        Amin = pos.y;
        Amax = Amin + size.y;
        Bmin = otherGO.pos.y;
        Bmax = Bmin + otherGO.size.y;
        if (Bmin > Amin)
            Amin = Bmin;
        if (Bmax < Amax)
            Amax = Bmax;
        inters.y = Amax - Amin;
        
        return true;
    }
    else
        return false;
}







Color:: Color() :
   m_color (0xffffffff),
         r ( *((Uint8*)&m_color) ),
         g ( *(&r+1) ),
         b ( *(&r+2) ),
         a ( *(&r+3) )
{}

Color:: Color(const Uint32& newColor) :
r ( *((Uint8*)&m_color) ),
g ( *(&r+1) ),
b ( *(&r+2) ),
a ( *(&r+3) )
{
    m_color = newColor;
}

       Color::  operator Uint32  () const           {
    return m_color;
}
Color& Color::  operator =       (const Color& newColor)  {
    
    m_color = newColor.m_color;
    
    return *this;
}
Color& Color::  operator =       (const Uint32& newColor)  {
    
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






void RectLine:: render()  {
    
    SDL_Rect rect = {};
    rect.x = static_cast<int>( pos.x );
    rect.y = static_cast<int>( pos.y );
    rect.w = static_cast<int>( size.x );
    rect.h = static_cast<int>( size.y );
    
    SDL_SetRenderDrawColor(engine.window, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(engine.window, &rect);
}








Texture:: Texture() :
    w (m_w),
    h (m_h),
    m_sdlTexture (NULL),
    m_w (0),
    m_h (0)
{}
Texture:: Texture( SDL_Texture* sdlTexture, int width, int height ) :
w (m_w),
h (m_h)
{
    Texture();
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
    m_clipRect (NULL),
       texture (),
          flip (0),
           rot (0.)
{}

void Image::  render()  {
    
    SDL_Rect toRect;
    
    toRect.x  = (int)pos.x;
	toRect.y  = (int)pos.y;
    toRect.w  = int( size.x * (float)texture.w );
    toRect.h  = int( size.y * (float)texture.h );
    
    SDL_RenderCopyEx( engine.window, texture, m_clipRect, &toRect, rot, NULL, (SDL_RendererFlip)flip );
}
























