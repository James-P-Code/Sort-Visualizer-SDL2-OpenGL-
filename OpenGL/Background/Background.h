#pragma once
#include "../RenderObject/RenderObject.h"
#include "stb_image.h"
#include <iostream>

class Background : public RenderObject
{
public:
	Background();
	void draw() const override;

private:
	unsigned char* imageData;
	GLuint texture;
};

