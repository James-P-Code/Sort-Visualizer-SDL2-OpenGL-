#pragma once
#include "../Shader/Shader.h"
#include "../Buffer/Buffer.h"

class RenderObject
{
public:
	virtual void draw() = 0;

protected:
	Shader shader;
	Buffer buffer;
};