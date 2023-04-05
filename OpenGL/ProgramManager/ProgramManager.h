#pragma once
#include "../RenderWindow/RenderWindow.h"
#include "../ShaderManager/ShaderManager.h"
#include "../BarChart/BarChart.h"

class ProgramManager final
{
public:
	ProgramManager();
	void updateWindow();

private:
	RenderWindow renderWindow;
	BarChart barChart;
	ShaderManager shaderManager;
};

