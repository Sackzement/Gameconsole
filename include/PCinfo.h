#pragma once
#include <SDL2/SDL_video.h>
#include "types.h"


class Display  {
public:
    int                num;
    std::string        name;
    SDL_Rect           bounds;
    int                numModes;
    
std::vector<SDL_DisplayMode>  modes;
    
    
    Display();
    Display(const int& num);
    void setDisplayNum(const int& newNum);
    
    SDL_DisplayMode getLargesMode() const;
};

class PCinfo  {
public:
    const int numVideoDrivers;
    const int numDisplays;
    const int numRenderDrivers;
    
    std::vector<Display>  displays;
    
    PCinfo();
    
};