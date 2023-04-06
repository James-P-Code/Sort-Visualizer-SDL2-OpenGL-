#pragma once
#include "../ProgramState/UnsortedState.h"
#include "../ProgramState/SortingState.h"
#include <memory>

class ProgramManager final
{
public:
	ProgramManager();
	void update();
	void render();
	void handleEvent(SDL_Event& event);
	void changeState();
	void setState(std::unique_ptr<ProgramState> newState);

private:
	RenderWindow renderWindow;
	BarChart barChart;
	ShaderManager shaderManager;
	std::unique_ptr<ProgramState> currentState;
	bool changeStateStatus = false;
};