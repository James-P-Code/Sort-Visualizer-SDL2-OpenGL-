#include "FrameBuffer.h"

void FrameBuffer::createFrameBuffer()
{
	glCreateFramebuffers(1, &frameBufferObject);

	glCreateTextures(GL_TEXTURE_2D, 1, &colorBuffer);
	glTextureParameteri(colorBuffer, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(colorBuffer, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureStorage2D(colorBuffer, 1, GL_RGB8, windowWidth, windowHeight);
	glNamedFramebufferTexture(frameBufferObject, GL_COLOR_ATTACHMENT0, colorBuffer, 0);

//	glCreateRenderbuffers(1, &renderBufferObject);
//	glNamedRenderbufferStorage(renderBufferObject, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
//	glNamedFramebufferRenderbuffer(frameBufferObject, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);
}

void FrameBuffer::createMultiColorBufferFrameBuffer()
{
	unsigned int colorBuffers[2];
	unsigned int colorAttachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

	glCreateFramebuffers(1, &frameBufferObject);
	glCreateTextures(GL_TEXTURE_2D, 2, dualColorBuffers);

	for (unsigned int i = 0; i < 2; ++i)
	{
		glTextureStorage2D(dualColorBuffers[i], 1, GL_RGB8, windowWidth, windowHeight);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glNamedFramebufferTexture(frameBufferObject, GL_COLOR_ATTACHMENT0 + i, dualColorBuffers[i], 0);
	}

	glCreateRenderbuffers(1, &renderBufferObject);
	glNamedRenderbufferStorage(renderBufferObject, GL_DEPTH_COMPONENT, windowWidth, windowHeight);
	glNamedFramebufferRenderbuffer(frameBufferObject, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);

	glNamedFramebufferDrawBuffers(frameBufferObject, 2, colorAttachments);
}

void FrameBuffer::createMultiBufferFrameBuffer()
{
	for (GLuint i = 0; i < 2; ++i)
	{
		glCreateFramebuffers(1, &dualFrameBufferObjects[i]);
		glCreateTextures(GL_TEXTURE_2D, 1, &dualColorBuffers[i]);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureStorage2D(dualColorBuffers[i], 1, GL_RGBA, windowWidth, windowHeight);
		glTextureSubImage2D(dualColorBuffers[i], 0, 0, 0, windowWidth, windowHeight, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glNamedFramebufferTexture(dualFrameBufferObjects[i], GL_COLOR_ATTACHMENT0, dualColorBuffers[i], 0);
	}
}

GLuint& FrameBuffer::getMultiBuffer(const size_t bufferIndex)
{
	return dualFrameBufferObjects[bufferIndex];
}

GLuint& FrameBuffer::getDualColorBuffer(const size_t bufferIndex)
{
	return dualColorBuffers[bufferIndex];
}

const GLuint& FrameBuffer::getFrameBuffer() const
{
	return frameBufferObject;
}

const GLuint& FrameBuffer::getColorBuffer() const
{
	return colorBuffer;
}

const glm::vec4* FrameBuffer::getScreenSpaceVerticesAndTextureCoordinates() const
{
	return screenSpaceVerticesAndTextureCoordinates;
}