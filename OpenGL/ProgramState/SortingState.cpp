#include "SortingState.h"

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
		}
		
	}

	sortAlgorithm->sort();
}

void SortingState::render(RenderWindow& renderWindow, ShaderManager& shaderManager, BarChart& barChart)
{
	constexpr int bufferIndexOffset = 9;

	renderWindow.setRectangleToHighlight(sortAlgorithm->getRectangleToHighlight());

	if (!barChart.getVerticesToSwap().empty())
	{
		shaderManager.updateVertexBuffer(sortAlgorithm->getFirstSwapIndex(), sortAlgorithm->getSecondSwapIndex(), barChart.getVerticesToSwap());
	//	shaderManager.updateVertexBuffer(barChart.getSwapIndex() - bufferIndexOffset, barChart.getVerticesToSwap());
	}

	renderWindow.updateWindow(shaderManager, barChart);
	barChart.clearSwaps();
}

void SortingState::handleEvent(SDL_Event& event)
{

}

void SortingState::changeState(ProgramManager& programManager)
{

}