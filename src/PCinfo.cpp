#include "../include/PCinfo.h"
#include <SDL2/SDL_render.h>



Display::  Display() :
num(-1),
name(""),
bounds(),
numModes(0),
modes()
{}


Display::  Display(const int& newNum)
{
    setDisplayNum(newNum);
}



void Display::  setDisplayNum(const int& newNum)
{
    num       = newNum;
    name      = SDL_GetDisplayName(num);
    SDL_GetDisplayBounds(num, &bounds);
    numModes  = SDL_GetNumDisplayModes(num);
    
    modes.clear();
    
    for (int i=0; i<numModes; ++i)  {
        modes.push_back(SDL_DisplayMode());
        SDL_GetDisplayMode(num, i, &(modes.back()) );
    }
}



SDL_DisplayMode Display::  getLargesMode() const  {
    
    SDL_DisplayMode ret = SDL_DisplayMode();
    
    for (int i=0; i<modes.size(); ++i)  {
        
        if ( modes[i].w > ret.w )
            ret = modes[i];
    }
    
    return ret;
}







PCinfo::  PCinfo() :
numVideoDrivers(SDL_GetNumVideoDrivers()),
numDisplays(SDL_GetNumVideoDisplays()),
numRenderDrivers(SDL_GetNumRenderDrivers()),
displays()
{
    for (int i=0; i<numDisplays; ++i)  {
        displays.push_back(Display());
        displays.back().setDisplayNum(i);
    }
}