#pragma once
#include <SDL.h>

class SDLSubSystem
{
protected:
	SDLSubSystem() { SDL_Init(SDL_INIT_VIDEO); }
	~SDLSubSystem() { SDL_Quit(); }
};