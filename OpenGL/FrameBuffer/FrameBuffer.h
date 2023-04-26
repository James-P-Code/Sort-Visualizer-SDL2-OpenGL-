#pragma once
#include <GL/glew.h>
#include "../Constants.h"

class FrameBuffer
{
public:
	~FrameBuffer();
	void createFrameBuffer();
	void createMultiColorBufferFrameBuffer();
	void createMultiBufferFrameBuffer();
	const GLuint& getFrameBuffer() const;
	const GLuint& getColorBuffer() const;
	GLuint& getMultiBuffer(const size_t);
	GLuint& getDualColorBuffer(const size_t);

private:
	GLuint frameBuffer, colorBuffer, renderBufferObject;
	GLuint dualFrameBuffers[2], dualColorBuffers[2];
};