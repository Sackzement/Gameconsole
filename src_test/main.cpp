
#include <stdio.h>
#include <iostream>
using namespace std;
#include <SDL2/SDL.h>



class A  {
public:
    A() {}
    void (*render)()  = nullptr;
    
    bool setTarget()  {return true;}
    
    bool getTargetSurface()   {return true;}
    bool getTargetRenderer()  {return true;}
    
protected:
    void* target  = nullptr;
    
    virtual void renderToTargetSurface()   {}
    virtual void renderToTargetRenderer()  {}
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
class  Shape : public A  {
public:
    Shape()  {}
    Color color;
protected:
    void setRenderColor()  {}
};

struct Position  {
    int x  = 0;
    int y  = 0;
};
class  Pixel : public Shape, public Position  {
public:
    Pixel() : Shape()  {}
protected:
    void renderToTargetRenderer()  override  {}
};




bool         RenderObject::  RenderObject() {
    
    if ( ! setTarget(windowRenderer) )
        setTarget(windowSurface);
}
bool         RenderObject::  setTarget(SDL_Surface* sdlSurf) {
    
    if ( ! sdlSurf )
        return false;
    else  {
        target = sdlSurf;
        render = &renderToSurface ;
        return true;
    }
}
bool         RenderObject::  setTarget(SDL_Renderer* sdlRend) {
    
    if ( ! sdlRend )
        return false;
    else  {
        target = sdlRend;
        render = &renderToRenderer ;
        return true;
    }
}
virtual void RenderObject::  renderToTargetSurface()   {}
virtual void RenderObject::  renderToTargetRenderer()  {}

Shape::  Shape() : RenderObject()  {}
void Shape::  setRenderColor()  {
    
    SDL_SetRenderDrawColor( (SDL_Renderer*)target, color.r, color.g, color.b, color.a);
}

Pixel::  Pixel() : Shape()  {}
void Pixel::  renderToTargetRenderer() override {
    
    setRenderColor();
    SDL_RenderDrawRect( (SDL_Renderer*)target, toRect);
}





int main ()  {
    
    cout << "ululu" << endl;
    
    Pixel p;
    
    return 0;
}












