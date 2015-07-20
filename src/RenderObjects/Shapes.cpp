#include "Shapes.h"






Pixel::  Pixel() : Shape()  {}
void Pixel::  renderToTargetRenderer() override {
    
    setRenderColor();
    SDL_RenderDrawRect( (SDL_Renderer*)target, toRect);
}