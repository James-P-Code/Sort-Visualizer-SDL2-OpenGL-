#include "ProgramManager.h"

ProgramManager::ProgramManager()
{
	shaderManager.loadShader("myshader.vert", "myshader.frag", barChart);
}

void ProgramManager::updateWindow()
{
	renderWindow.updateWindow(shaderManager, barChart);
}