#include <SDL.h>
#include "ProgramManager/ProgramManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
			programManager.handleEvent(event);
		}
		programManager.update();
		programManager.render();
		programManager.changeState();

		frameEnd = SDL_GetTicks() - frameStart;

		if (frameEnd < frameDelay) // cap the fps to the maxFPS constant value
		{
			SDL_Delay(frameDelay - frameEnd);
		}
	}
	return 0;
}