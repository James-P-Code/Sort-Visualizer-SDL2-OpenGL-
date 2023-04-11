#pragma once
#include "ProgramState.h"

class UnsortedState final : public ProgramState
{
public:
	UnsortedState();
	virtual ~UnsortedState() {};

private:
	void update(BarChart& barChart) override;
	void render(RenderWindow& renderWindow, BarChart& barChart) override;
	void handleEvent(SDL_Event& event) override;
	void changeState(ProgramManager& programManager) override;
};

