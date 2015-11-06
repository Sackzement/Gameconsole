#pragma once

#include <SDL2/SDL_video.h>
#include <SDL2\SDL_render.h>



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
	SDL_Window*  createWindow(const char* title, int x, int y, int w, int h, Uint32 flags);
	void         destroyWindow(SDL_Window* window);
};


class RENDER
{
public:
	SDL_Renderer*  createRenderer(SDL_Window* window, int index, Uint32 flags);
	SDL_Texture*   createTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);
	void           destroyRenderer(SDL_Renderer* renderer);
	void           destroyTexture(SDL_Texture* texture);
	int            renderClear(SDL_Renderer* renderer);
	int            renderCopyEx(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip);
	void           renderPresent(SDL_Renderer* renderer);
	int            setRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
};



class SDF
{
public:
	INITQUIT initquit;
	DISWIN   disWin;
	RENDER   render;
};



static SDF sdf;