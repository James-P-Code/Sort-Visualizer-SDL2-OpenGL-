#include "ProgramManager.h"

ProgramManager::ProgramManager() : currentState(std::make_unique<UnsortedState>())
{
	//renderObjects.push_back(&background);
	renderObjects.push_back(&barChart);
}

void ProgramManager::update()
{
	currentState->update(barChart);
}

void ProgramManager::render()
{
	currentState->render(renderWindow, renderObjects);
}

void ProgramManager::handleEvent(SDL_Event& event)
{
	currentState->handleEvent(event);
}

void ProgramManager::changeState()
{
	currentState->changeState(*this);
}

void ProgramManager::setState(std::unique_ptr<ProgramState> newState)
{
	currentState = std::move(newState);
}