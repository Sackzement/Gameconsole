#pragma once
#include <SDL2/SDL_syswm.h>


class Window2
{
private:
	SDL_Window* windowSDL;

public:
	SDL_Window*  create(const char* title, int x, int y, int w, int h, Uint32 flags);
	SDL_Window*  createFrom(const void* data);
	void         destroy();

	void  hide();
	void  maximize();
	void  minimize();
	void  raise();
	void  restore();
	void  show();
	int   updateSurface();
	int   updateSurfaceRects(const SDL_Rect* rects, int numrects);

	float         getBrightness();
	void*         getData(const char* name);
	int           getDisplayIndex();
	int           getDisplayMode(SDL_DisplayMode* mode);
	Uint32        getFlags();
	int           getGammaRamp(Uint16* red, Uint16* green, Uint16* blue);
	SDL_bool      getGrab();
	Uint32        getID();
	void          getMaximumSize(int* w, int* h);
	void          getMinimumSize(int* w, int* h);
	Uint32        getPixelFormat();
	void          getPosition(int* x, int* y);
	void          getSize(int* w, int* h);
	SDL_Surface*  getSurface();
	const char*   getTitle();
	SDL_bool      getWMInfo(SDL_SysWMinfo* info);

	void   setBordered(SDL_bool bordered);
	int    setBrightness(float brightness);
	void*  setData(const char* name, void* userdata);
	int    setDisplayMode(const SDL_DisplayMode* mode);
	int    setFullscreen(Uint32 flags);
	int    setGammaRamp(const Uint16* red, const Uint16* green, const Uint16* blue);
	void   setGrab(SDL_bool grabbed);
	//int    setHitTest(SDL_HitTest callback, void* callback_data);
	void   setIcon(SDL_Surface* icon);
	void   setMaximumSize(int w, int h);
	void   setMinimumSize(int w, int h);
	void   setPosition(int x, int y);
	void   setSize(int w, int h);
	void   setTitle(const char* title);
};




