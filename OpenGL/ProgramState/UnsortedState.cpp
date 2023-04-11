#include "UnsortedState.h"
#include "../ProgramManager/ProgramManager.h"
#include "../BarChart/BarChart.h"
#include "../RenderWindow/RenderWindow.h"

UnsortedState::UnsortedState()
{
	sortType = SortAlgorithm::SortType::None;
}

void UnsortedState::update(BarChart& barChart) {}

void UnsortedState::render(const RenderWindow& renderWindow, const std::vector<RenderObject*>& renderObjects) const
{
	renderWindow.clearWindow();
	for (const auto& renderObject : renderObjects)
	{
		renderObject->draw();
	}
	renderWindow.updateWindow();
}

void UnsortedState::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_1: sortType = SortAlgorithm::SortType::BubbleSort; break;
			case SDLK_2: sortType = SortAlgorithm::SortType::SelectionSort; break;
			case SDLK_3: sortType = SortAlgorithm::SortType::InsertionSort; break;
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