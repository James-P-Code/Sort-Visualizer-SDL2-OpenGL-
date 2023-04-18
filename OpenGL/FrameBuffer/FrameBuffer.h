#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../Constants.h"

class FrameBuffer
{
public:
	void createFrameBuffer();
	const GLuint& getFrameBuffer() const;
	const GLuint& getFrameBufferTexture() const;
	const glm::vec4* getScreenSpaceVerticesAndTextureCoordinates() const;

private:
	GLuint frameBufferObject, textureColorBuffer, renderBufferObject;

	static constexpr glm::vec4 screenSpaceVerticesAndTextureCoordinates[4] =
	{
		glm::vec4(-1.0f, 1.0f,    0.0f, 1.0f),
		glm::vec4(1.0f, 1.0f,    1.0f, 1.0f),
		glm::vec4(1.0f, -1.0f,   1.0f, 0.0f),
		glm::vec4(-1.0f, -1.0f,   0.0f, 0.0f)
	};
};