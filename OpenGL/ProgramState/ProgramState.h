#pragma once
#include "../SortAlgorithm/BubbleSort.h"
#include "../SortAlgorithm/SelectionSort.h"
#include "../SortAlgorithm/InsertionSort.h"

class RenderWindow;
class ProgramManager;

class ProgramState
{
public:
	virtual ~ProgramState() {};
	virtual void update(BarChart& barChart) = 0;
	virtual void render(const RenderWindow& renderWindow, const std::vector<RenderObject*>& renderObjects) const = 0;
	virtual void handleEvent(SDL_Event& event) = 0;
	virtual void changeState(ProgramManager& programManager) = 0;

protected:
	SortAlgorithm::SortType sortType = SortAlgorithm::SortType::None;
	bool changeStateStatus = false;
};