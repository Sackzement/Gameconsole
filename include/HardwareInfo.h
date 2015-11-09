#pragma once
#include <SDL2/SDL_video.h>
#include "types.h"


class DisplayInfo  {
public:
    int                idx;
    std::string        name;
    SDL_Rect           bounds;
    int                numModes;
    
std::vector<SDL_DisplayMode>  modes;
    
    
	void updateByIdx(int newNum);
    SDL_DisplayMode getLargesMode();
};

class HardwareInfo  {
private:
	std::string platform;
	int numCPUs;
	int CPUcacheLineSize;
	int RAM;
    int numVideoDrivers;
    int numDisplays;
    int numRenderDrivers;
    
	std::vector<DisplayInfo>  displays;
public:
	void update();
	std::string getPlatform();
	int getNumCPUs();
	int getCPUcacheLineSize();
	int getRAM();
	int getNumVideoDrivers();
	int getNumDisplays();
	int getNumRenderDrivers();
	DisplayInfo getDisplay(int num = 0);
    
};