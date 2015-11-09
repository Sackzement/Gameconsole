#include "../include/HardwareInfo.h"
#include <SDL2/SDL_render.h>






void DisplayInfo::updateByIdx(int newIdx)
{
	idx = newIdx;
    name      = SDL_GetDisplayName(idx);
	SDL_GetDisplayBounds(idx, &bounds);
	numModes = SDL_GetNumDisplayModes(idx);
    
    modes.clear();
    
    for (int i=0; i<numModes; ++i)  {
        modes.push_back(SDL_DisplayMode());
		SDL_GetDisplayMode(idx, i, &(modes.back()));
    }
}



SDL_DisplayMode DisplayInfo::getLargesMode()   
{
    
    SDL_DisplayMode ret = SDL_DisplayMode();
    
    for (int i=0; i<int(modes.size()); ++i)  {
        
        if ( modes[i].w > ret.w )
            ret = modes[i];
    }
    
    return ret;
}




#include <SDL2/SDL_cpuinfo.h>


void HardwareInfo::update()
{
	numVideoDrivers = SDL_GetNumVideoDrivers();
	numDisplays = SDL_GetNumVideoDisplays();
	numRenderDrivers = SDL_GetNumRenderDrivers();

    for (int i=0; i<numDisplays; ++i)  {
		displays.push_back(DisplayInfo());
		displays.back().updateByIdx(i);
    }

	platform = SDL_GetPlatform();
	numCPUs = SDL_GetCPUCount();
	CPUcacheLineSize = SDL_GetCPUCacheLineSize();
	RAM = SDL_GetSystemRAM();
}
std::string HardwareInfo::getPlatform()
{
	return platform;
}
int HardwareInfo::getNumCPUs()
{
	return numCPUs;
}
int HardwareInfo::getCPUcacheLineSize()
{
	return CPUcacheLineSize;
}
int HardwareInfo::getRAM()
{
	return RAM;
}
int HardwareInfo::getNumVideoDrivers()
{
	return numVideoDrivers;
}
int HardwareInfo::getNumDisplays()
{
	return numDisplays;
}
int HardwareInfo::getNumRenderDrivers()
{
	return numRenderDrivers;
}
DisplayInfo HardwareInfo::getDisplay(int num)
{
	DisplayInfo ret;

	if (numDisplays > 0 )
	{
		if (num < numDisplays)
			ret = displays[num];
	}

	return ret;
}