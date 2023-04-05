#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <memory>
#include "../SDLSubSystem/SDLSubSystem.h"

class BarChart;
class ShaderManager;

class RenderWindow final : public SDLSubSystem
{
public:
	RenderWindow();
	void updateWindow(ShaderManager& shaderManager, BarChart& barChart);

private:
	struct SDL_Deleter final
	{
		void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
		void operator()(SDL_GLContext* p) const { SDL_GL_DeleteContext(*p); }
	};

	static constexpr int windowWidth = 800, windowHeight = 600;
	std::unique_ptr<SDL_Window, SDL_Deleter> window;
	std::unique_ptr<SDL_GLContext, SDL_Deleter> glContext;
};