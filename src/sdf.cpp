#include "../include/sdf.h"
#include <SDL2/SDL.h>

SDL_Window*  DISWIN::  createWindow(const char* title, int x, int y, int w, int h, Uint32 flags)
{
	return SDL_CreateWindow(title, x, y, w, h, flags);
}
void         DISWIN::  destroyWindow(SDL_Window* window)
{
	SDL_DestroyWindow(window);
}


int     INITQUIT::  init(Uint32 flags)
{
	return SDL_Init(flags);
}
int     INITQUIT::  initSubSystem(Uint32 flags)
{
	return SDL_InitSubSystem(flags);
}
void    INITQUIT::  quit()
{
	SDL_Quit();
}
void    INITQUIT::  quitSubSystem(Uint32 flags)
{
	SDL_QuitSubSystem(flags);
}
Uint32  INITQUIT::  wasInit(Uint32 flags)
{
	return SDL_WasInit(flags);
}