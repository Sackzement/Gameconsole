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


SDL_Renderer*  RENDER::  createRenderer(SDL_Window* window, int index, Uint32 flags)
{
	return SDL_CreateRenderer(window, index, flags);
}
SDL_Texture*   RENDER::  createTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface)
{
	return SDL_CreateTextureFromSurface(renderer, surface);
}
void           RENDER::  destroyRenderer(SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
}
void           RENDER::  destroyTexture(SDL_Texture* texture)
{
	SDL_DestroyTexture(texture);
}
int            RENDER::  renderClear(SDL_Renderer* renderer)
{
	return SDL_RenderClear(renderer);
}
int            RENDER::  renderCopyEx(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip)
{
	return SDL_RenderCopyEx(renderer, texture, srcrect, dstrect, angle, center, flip);
}
void           RENDER::  renderPresent(SDL_Renderer* renderer)
{
	SDL_RenderPresent(renderer);
}
int            RENDER::  setRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
