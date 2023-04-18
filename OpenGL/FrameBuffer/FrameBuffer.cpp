#include "FrameBuffer.h"

void FrameBuffer::createFrameBuffer()
{
	glCreateFramebuffers(1, &frameBufferObject);

	glCreateTextures(GL_TEXTURE_2D, 1, &textureColorBuffer);
	glTextureStorage2D(textureColorBuffer, 1, GL_RGB8, windowWidth, windowHeight);
	glTextureParameteri(textureColorBuffer, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(textureColorBuffer, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glNamedFramebufferTexture(frameBufferObject, GL_COLOR_ATTACHMENT0, textureColorBuffer, 0);

	glCreateRenderbuffers(1, &renderBufferObject);
	glNamedRenderbufferStorage(renderBufferObject, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
	glNamedFramebufferRenderbuffer(frameBufferObject, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);
}

const GLuint& FrameBuffer::getFrameBuffer() const
{
	return frameBufferObject;
}

const GLuint& FrameBuffer::getFrameBufferTexture() const
{
	return textureColorBuffer;
}

const glm::vec4* FrameBuffer::getScreenSpaceVerticesAndTextureCoordinates() const
{
	return screenSpaceVerticesAndTextureCoordinates;
}