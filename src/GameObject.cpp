#include "../include/GameObject.h"
#include <algorithm>

GameObject:: GameObject()
:
pos(0.,0.),
size(1.,1.),
m_children(nullptr)
{}

GameObject GameObject:: copy() const  {
    
    GameObject go;
    
    go.pos         = this->pos;
    go.size        = this->size;
    go.m_children  = this->m_children;
    
    return go;
}
void GameObject:: input() const  {}
void GameObject:: update() const {}
void GameObject:: render( SDL_Renderer* rend ) const {}

void GameObject:: renderChildren(SDL_Renderer* rend) const  {
    
    if ( hasChildren() )  {
        
        std::vector<GameObject*>::iterator it;
        for (it = m_children->begin(); it != m_children->end(); ++it)  {
            
            GameObject offset = (*it)->copy();
            
            offset.pos    = this->pos + (offset.pos * this->size);
            offset.size  *= this->size;
            
            offset.render(rend);
            offset.renderChildren(rend);
        }
    }
}
bool GameObject:: hasChildren() const  {
    
    if ( m_children == nullptr
      || m_children->empty() )
        return false;
    else
        return true;
}
bool GameObject:: hasChild(GameObject* ch) const  {
    
    if ( m_children != nullptr
     && std::find(m_children->begin(),m_children->end(),ch) != m_children->end() )
        return true;
    else
        return false;
}
void GameObject:: addChild(GameObject* ch)  {
    
    if ( ch )  {
        
        if ( ! m_children )
            m_children = new std::vector<GameObject*>();
            
        if ( ! hasChild(ch) )
            m_children->push_back(ch);
    }
    
}
void GameObject:: removeChild(GameObject* ch)  {
    
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






void RectFill:: render( SDL_Renderer* rend ) const  {
    
    SDL_Rect rect = {};
    rect.x = static_cast<int>( pos.x );
    rect.y = static_cast<int>( pos.y );
    rect.x = static_cast<int>( size.x );
    rect.y = static_cast<int>( size.y );
    
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rend, &rect);
}








