#pragma once
#include "ProgramState.h"
#include <memory>
#include <iostream>

class SortingState final : public ProgramState
{
public:
	SortingState(const SortAlgorithm::SortType& sortType);
	virtual ~SortingState() {};

private:
	std::unique_ptr<SortAlgorithm> sortAlgorithm;

	void update(BarChart& barChart) override;
	void render(const RenderWindow& renderWindow, const std::vector<RenderObject*>& renderObjects) const override;
	void handleEvent(SDL_Event& event) override;
	void changeState(ProgramManager& programManager) override;
};