#pragma once
#include "../Shader/Shader.h"

class RenderObject
{
public:
	virtual void draw() const = 0;

protected:
	Shader shader;
};