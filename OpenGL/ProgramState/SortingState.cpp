#include "SortingState.h"
#include "../ProgramManager/ProgramManager.h"
#include "../BarChart/BarChart.h"
#include "../RenderWindow/RenderWindow.h"

SortingState::SortingState(const SortAlgorithm::SortType& sortType)
{
	this->sortType = sortType;
}

void SortingState::update(BarChart& barChart)
{
	if (!sortAlgorithm)
	{
		switch (sortType)
		{
			case SortAlgorithm::SortType::BubbleSort: sortAlgorithm = std::make_unique<BubbleSort>(barChart); break;
			case SortAlgorithm::SortType::SelectionSort: sortAlgorithm = std::make_unique<SelectionSort>(barChart); break;
			case SortAlgorithm::SortType::InsertionSort: sortAlgorithm = std::make_unique<InsertionSort>(barChart); break;
		}
		
	}

	sortAlgorithm->sort();
}

void SortingState::render(const RenderWindow& renderWindow, const std::vector<RenderObject*>& renderObjects) const
{
	renderWindow.clearWindow();
	for (const auto& renderObject : renderObjects)
	{
		renderObject->draw();
	}
	renderWindow.updateWindow();
}

void SortingState::handleEvent(SDL_Event& event)
{

}

void SortingState::changeState(ProgramManager& programManager)
{

}