#include "Shape.h"







     Shape::  Shape() : RenderObject()  {}
void Shape::  setRenderColor()  {
    
    SDL_SetRenderDrawColor( (SDL_Renderer*)target, color.r, color.g, color.b, color.a);
}