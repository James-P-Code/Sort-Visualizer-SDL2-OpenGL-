#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../Constants.h"

class FrameBuffer
{
public:
	void createFrameBuffer();
	void createMultiColorBufferFrameBuffer();
	void createMultiBufferFrameBuffer();
	const GLuint& getFrameBuffer() const;
	const GLuint& getColorBuffer() const;
	GLuint& getMultiBuffer(const size_t);
	GLuint& getDualColorBuffer(const size_t);
	const glm::vec4* getScreenSpaceVerticesAndTextureCoordinates() const;

private:
	GLuint frameBufferObject, colorBuffer, renderBufferObject;
	GLuint dualFrameBufferObjects[2], dualColorBuffers[2];

	static constexpr glm::vec4 screenSpaceVerticesAndTextureCoordinates[4] =
	{
		glm::vec4(-1.0f, 1.0f,    0.0f, 1.0f),
		glm::vec4(1.0f, 1.0f,    1.0f, 1.0f),
		glm::vec4(1.0f, -1.0f,   1.0f, 0.0f),
		glm::vec4(-1.0f, -1.0f,   0.0f, 0.0f)
	};
};