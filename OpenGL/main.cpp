#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <GL/GLU.h>
#include "ProgramManager/ProgramManager.h"

int main(int argc, char* argv[])
{
	constexpr int maxFPS = 144;
	constexpr int frameDelay = 1000 / maxFPS;
	uint32_t frameStart, frameEnd;
	ProgramManager programManager;
	bool quit = false;
	SDL_Event event;

	while (!quit)
	{
		frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		programManager.updateWindow();

		frameEnd = SDL_GetTicks() - frameStart;

		if (frameEnd < frameDelay) // cap the fps to the maxFPS constant value
		{
			SDL_Delay(frameDelay - frameEnd);
		}
	}
	return 0;
}