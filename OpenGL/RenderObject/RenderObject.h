#pragma once
#include "../Shader/Shader.h"

class RenderObject
{
public:
	virtual void draw() = 0;

protected:
	Shader shader;
};