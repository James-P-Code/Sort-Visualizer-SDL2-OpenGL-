#pragma once
#include <unordered_map>
#include "../Shader/Shader.h"
#include "../VertexBuffer/VertexBuffer.h"
#include "../FrameBuffer/FrameBuffer.h"

class RenderObject
{
public:
	virtual ~RenderObject() {};
	virtual void draw() = 0;

protected:
	FrameBuffer frameBuffer;
};