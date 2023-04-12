#pragma once
#include <memory>
#include <vector>
#include "../RenderWindow/RenderWindow.h"
#include "../BarChart/BarChart.h"
#include "../Background/Background.h"
#include "../ProgramState/UnsortedState.h"
#include "../ProgramState/SortingState.h"

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
	Background background;
	std::vector<RenderObject*> renderObjects;
	std::unique_ptr<ProgramState> currentState;
};