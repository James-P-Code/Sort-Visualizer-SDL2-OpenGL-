#include "UnsortedState.h"
#include "../ProgramManager/ProgramManager.h"

UnsortedState::UnsortedState()
{
	sortType = SortAlgorithm::SortType::None;
}

void UnsortedState::update(BarChart& barChart) {}

void UnsortedState::render(RenderWindow& renderWindow, ShaderManager& shaderManager, BarChart& barChart)
{
	renderWindow.updateWindow(shaderManager, barChart);
}

void UnsortedState::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_1: sortType = SortAlgorithm::SortType::BubbleSort; break;
			case SDLK_2: sortType = SortAlgorithm::SortType::SelectionSort; break;
		}
		
		if (sortType != SortAlgorithm::SortType::None)
		{
			changeStateStatus = true;
		}
	}
}

void UnsortedState::changeState(ProgramManager& programManager)
{
	if (changeStateStatus)
	{
		programManager.setState(std::make_unique<SortingState>(sortType));
	}
}