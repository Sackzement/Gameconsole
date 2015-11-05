#pragma once

#include <SDL2/SDL_video.h>



class INITQUIT
{
public:
	int     init(Uint32 flags);
	int     initSubSystem(Uint32 flags);
	void    quit();
	void    quitSubSystem(Uint32 flags);
	Uint32  wasInit(Uint32 flags);
};



class DISWIN
{
public:
	SDL_Window* createWindow(const char* title, int x, int y, int w, int h, Uint32 flags);
	void destroyWindow(SDL_Window* window);
};



class SDF
{
public:
	INITQUIT initquit;
	DISWIN   disWin;
};



static SDF sdf;