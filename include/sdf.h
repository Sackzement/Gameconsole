#pragma once
#include "types.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_assert.h>
#include <SDL2\SDL_version.h>
#include <SDL2/SDL_revision.h>

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_clipboard.h>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_gamecontroller.h>

#include <SDL2/SDL_haptic.h>

#include <SDL2/SDL_audio.h>

#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_mutex.h>
#include <SDL2/SDL_atomic.h>

#include <SDL2/SDL_timer.h>

#include <SDL2/SDL_filesystem.h>
#include <SDL2/SDL_rwops.h>

#include <SDL2/SDL_loadso.h>

#include <SDL2/SDL_platform.h>
#include <SDL2/SDL_cpuinfo.h>
#include <SDL2/SDL_endian.h>
#include <SDL2/SDL_bits.h>

#include <SDL2/SDL_power.h>

#include <SDL2/SDL_system.h>
#include <SDL2/SDL_stdinc.h>




class INITQUIT
{
private:
	class FLAGS
	{
	public:
		Uint32 timer           = 0x00000001;
		Uint32 audio           = 0x00000010;
		Uint32 video           = 0x00000020;
		Uint32 joystick        = 0x00000200;
		Uint32 haptic          = 0x00001000;
		Uint32 gamecontroller  = 0x00002000;
		Uint32 events          = 0x00004000;
		Uint32 noparachute     = 0x00100000;
		Uint32 everything      = timer | audio | video | joystick | haptic
			                     | gamecontroller | events | noparachute;
	};
public:
	FLAGS   flags;
	int     SDL_Init(Uint32 flags);
	int     SDL_InitSubSystem(Uint32 flags);
	void    SDL_Quit();
	void    SDL_QuitSubSystem(Uint32 flags);
	Uint32  SDL_WasInit(Uint32 flags);
};


class HINTS
{
public:
	void      SDL_AddHintCallback(cchar* name, SDL_HintCallback callback, void* userdata);
	void      SDL_ClearHints();
	void      SDL_DelHintCallback(cchar* name, SDL_HintCallback callback, void* userdata);
	cchar*    SDL_GetHint(cchar* name);
	SDL_bool  SDL_SetHint(cchar* name, cchar* value);
	SDL_bool  SDL_SetHintWithPriority(cchar* name, cchar* value, SDL_HintPriority priority);
};


class VIDEO
{
public:
	int      SDL_CreateWindowAndRenderer(int width, int height, Uint32 window_flags, SDL_Window** window, SDL_Renderer** renderer);
	void     SDL_DisableScreenSaver();
	void     SDL_EnableScreenSaver();
	SDL_bool SDL_IsScreenSaverEnabled();

	void SDL_GetClosestDisplayMode();
	void SDL_GetCurrentDisplayMode();
	void SDL_GetCurrentVideoDriver();
	void SDL_GetDesktopDisplayMode();
	void SDL_GetDisplayBounds();
	void SDL_GetDisplayDPI();
	void SDL_GetDisplayMode();
	void SDL_GetDisplayName();

	void SDL_GetNumDisplayModes();
	void SDL_GetNumVideoDisplays();
	void SDL_GetNumVideoDrivers();

	void SDL_GetVideoDriver();

	void SDL_ShowMessageBox();
	void SDL_ShowSimpleMessageBox();
	void SDL_VideoInit();
	void SDL_VideoQuit();
};


class WINDOW
{
public:
	void SDL_CreateWindow();
	void SDL_CreateWindowFrom();
	void SDL_DestroyWindow();

	void SDL_GetGrabbedWindow();
	void SDL_GetWindowFromID();


	void SDL_HideWindow();
	void SDL_MaximizeWindow();
	void SDL_MinimizeWindow();
	void SDL_RaiseWindow();
	void SDL_RestoreWindow();
	void SDL_ShowWindow();
	void SDL_UpdateWindowSurface();
	void SDL_UpdateWindowSurfaceRects();


	void SDL_GetWindowBrightness();
	void SDL_GetWindowData();
	void SDL_GetWindowDisplayIndex();
	void SDL_GetWindowDisplayMode();
	void SDL_GetWindowFlags();
	void SDL_GetWindowGammaRamp();
	void SDL_GetWindowGrab();
	void SDL_GetWindowID();
	void SDL_GetWindowMaximumSize();
	void SDL_GetWindowMinimumSize();
	void SDL_GetWindowPixelFormat();
	void SDL_GetWindowPosition();
	void SDL_GetWindowSize();
	void SDL_GetWindowSurface();
	void SDL_GetWindowTitle();
	void SDL_GetWindowWMInfo();


	void SDL_SetWindowBrightness();
	void SDL_SetWindowBordered();
	void SDL_SetWindowData();
	void SDL_SetWindowDisplayMode();
	void SDL_SetWindowFullscreen();
	void SDL_SetWindowGammaRamp();
	void SDL_SetWindowGrab();
	void SDL_SetWindowHitTest();
	void SDL_SetWindowIcon();
	void SDL_SetWindowMaximumSize();
	void SDL_SetWindowMinimumSize();
	void SDL_SetWindowPosition();
	void SDL_SetWindowSize();
	void SDL_SetWindowTitle();
};


class RENDER
{
public:
	void SDL_GetNumRenderDrivers();
	void SDL_GetRenderDriverInfo();
	void SDL_GetRenderer();

	void SDL_GetRenderDrawBlendMode();
	void SDL_GetRenderDrawColor();
	void SDL_GetRenderTarget();
	void SDL_GetRendererInfo();
	void SDL_GetRendererOutputSize();

	SDL_Renderer*  SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags);
	SDL_Texture*   SDL_CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);
	void           SDL_DestroyRenderer(SDL_Renderer* renderer);
	void           SDL_DestroyTexture(SDL_Texture* texture);
	int            SDL_RenderClear(SDL_Renderer* renderer);
	void           SDL_RenderCopyEx();
	int            SDL_RenderCopyEx(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip);
	
	void SDL_RenderDrawLine();
	void SDL_RenderDrawLines();
	void SDL_RenderDrawPoint();
	void SDL_RenderDrawPoints();
	void SDL_RenderDrawRect();
	void SDL_RenderDrawRects();
	void SDL_RenderFillRect();
	void SDL_RenderFillRects();

	void SDL_RenderGetClipRect();
	void SDL_RenderGetLogicalSize();
	void SDL_RenderGetScale();
	void SDL_RenderGetViewport();

	void SDL_RenderReadPixels();
	void SDL_RenderSetClipRect();
	void SDL_RenderSetLogicalSize();
	void SDL_RenderSetScale();
	void SDL_RenderSetViewport();
	
	void SDL_RenderPresent(SDL_Renderer* renderer);
	int  SDL_SetRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SDL_SetRenderDrawBlendMode();
	void SDL_SetRenderDrawColor();
	void SDL_SetRenderTarget();
};



class SDF
{
public:
	INITQUIT  initquit;
	HINTS     hints;
	VIDEO     video;
	WINDOW    window;
	RENDER    render;
};



static SDF sdf;