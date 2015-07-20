#include "RenderObject.h"



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








