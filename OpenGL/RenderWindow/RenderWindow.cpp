#include "RenderWindow.h"
#include "../ShaderManager/ShaderManager.h"
#include "../BarChart/BarChart.h"

RenderWindow::RenderWindow()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	window = std::unique_ptr<SDL_Window, SDL_Deleter>(SDL_CreateWindow("Sort Visualizer", 
																		SDL_WINDOWPOS_CENTERED, 
																		SDL_WINDOWPOS_CENTERED, 
																		windowWidth, 
																		windowHeight, 
																		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN));
	glContext = std::unique_ptr<SDL_GLContext, SDL_Deleter>(new SDL_GLContext(SDL_GL_CreateContext(window.get())));
	glewExperimental = GL_TRUE;
	glewInit();
	SDL_GL_SetSwapInterval(1);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void RenderWindow::updateWindow(ShaderManager& shaderManager, BarChart& barChart)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	int shaderHighlightUniform = glGetUniformLocation(shaderManager.getProgramID(), "highlightVertex");
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(shaderManager.getProgramID());
	glUniform1i(shaderHighlightUniform, rectangleToHighlight);
	glBindVertexArray(shaderManager.getVertexArrayObject());
	glDrawElements(GL_TRIANGLES, shaderManager.getVerticesCount(), GL_UNSIGNED_SHORT, nullptr);

	SDL_GL_SwapWindow(window.get());
	//SDL_Delay(300);
}

void RenderWindow::setRectangleToHighlight(const GLint indexToHighlight)
{
	rectangleToHighlight = indexToHighlight;
}