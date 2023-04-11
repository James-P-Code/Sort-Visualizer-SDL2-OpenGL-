#pragma once
#include "ProgramState.h"

class UnsortedState final : public ProgramState
{
public:
	UnsortedState();
	virtual ~UnsortedState() {};

private:
	void update(BarChart& barChart) override;
	void render(const RenderWindow& renderWindow, const std::vector<RenderObject*>& renderObjects) const override;
	void handleEvent(SDL_Event& event) override;
	void changeState(ProgramManager& programManager) override;
};