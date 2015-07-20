#pragma once

#include "RenderObjects/Shapes.h"





/*/ RENDER OBJECTs
class RenderObject  {
public:
    RenderObject();
    void (*render)()  = nullptr;
    
    bool setTarget(SDL_Surface* sdlSurf);
    bool setTarget(SDL_Renderer* sdlRend);
    
    bool getTargetSurface();
    bool getTargetRenderer();
    
protected:
    void* target  = nullptr;
    
    virtual void renderToTargetSurface();
    virtual void renderToTargetRenderer();
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
class  Shape : public RenderObject  {
public:
    Shape();
    Color color;
protected:
    void setRenderColor();
};

struct Position  {
    int x  = 0;
    int y  = 0;
};
class  Pixel : public Shape, public Position  {
public:
    Pixel();
protected:
    void renderToTargetRenderer()  override;
};
struct Line : Shape, Position  {
    
    Position to;
    
    void renderToTargetRenderer()  override  {
        
        setRenderColor();
        SDL_RenderDrawLine( (SDL_Renderer*)target, x, y, to.x,to.y );
    }
};

struct Rect : Shape  {
    
    SDL_Rect* toRect  = NULL;
    
protected:
    void renderToTargetSurface() override;
    void renderToTargetRenderer() override;
};


struct FromToRect  {
    
    SDL_Rect*     fromRect  = NULL;
    SDL_Rect*     toRect    = NULL;
};
class  Surface : RenderObject, FromToRect  {
public:
    SDL_Surface*  fromSdlSurface  = nullptr;
    
    void renderToTargetSurface ()  override  {
        
        SDL_BlitSurface(fromSdlSurface, fromRect, (SDL_Surface*)target, toRect);
    }
    
    virtual ~Surface()  {}
};
struct AngleCenterFlip  {
    
    double            angle   = 0.;
    SDL_Point*        center  = NULL;
    SDL_RendererFlip  flip    = SDL_FLIP_NONE;
};
class  Texture : RenderObject, FromToRect, AngleCenterFlip  {
public:
    SDL_Texture*  fromTexture  = nullptr;
    SDL_Renderer* toRenderer   = nullptr;
    
    void renderToTargetRenderer ()  override  {
        
        if ( fromTexture && toRenderer )
            SDL_RenderCopyEx (toRenderer,fromTexture,fromRect,toRect,angle,center,flip);
    }
    
    virtual ~Texture()  {}
};
*/






