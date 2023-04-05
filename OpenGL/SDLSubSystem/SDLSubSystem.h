#pragma once
#include <SDL.h>
#include <iostream>

class SDLSubSystem
{
protected:
	SDLSubSystem() { SDL_Init(SDL_INIT_VIDEO); }
	~SDLSubSystem() { SDL_Quit(); }
};