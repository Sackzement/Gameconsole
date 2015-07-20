#pragma once






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