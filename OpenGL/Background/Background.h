#pragma once
#include "../RenderObject/RenderObject.h"
#include "stb_image.h"
#include <iostream>

class Background : public RenderObject
{
public:
	Background();
	void draw() override;

private:
	GLuint texture;
};

