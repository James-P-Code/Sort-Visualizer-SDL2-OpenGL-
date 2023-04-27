#include "FrameBuffer.h"

FrameBuffer::~FrameBuffer()
{
	glDeleteTextures(1, &colorBuffer);
	glDeleteTextures(2, dualColorBuffers);
	glDeleteFramebuffers(1, &frameBuffer);
	glDeleteFramebuffers(2, dualFrameBuffers);
}

void FrameBuffer::createFrameBuffer()
{
	glCreateFramebuffers(1, &frameBuffer);
	glCreateTextures(GL_TEXTURE_2D, 1, &colorBuffer);
	glTextureParameteri(colorBuffer, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(colorBuffer, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureStorage2D(colorBuffer, 1, GL_RGBA8, windowWidth, windowHeight);
	glNamedFramebufferTexture(frameBuffer, GL_COLOR_ATTACHMENT0, colorBuffer, 0);
}

void FrameBuffer::createMultiColorBufferFrameBuffer()
{
	constexpr int numberOfColorBuffers = 2;
	GLuint colorAttachments[numberOfColorBuffers] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

	glCreateFramebuffers(1, &frameBuffer);
	glCreateTextures(GL_TEXTURE_2D, 2, dualColorBuffers);

	for (unsigned int i = 0; i < numberOfColorBuffers; ++i)
	{
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureStorage2D(dualColorBuffers[i], 1, GL_RGBA8, windowWidth, windowHeight);
		glNamedFramebufferTexture(frameBuffer, GL_COLOR_ATTACHMENT0 + i, dualColorBuffers[i], 0);
	}

	glNamedFramebufferDrawBuffers(frameBuffer, numberOfColorBuffers, colorAttachments);
}

void FrameBuffer::createMultiBufferFrameBuffer()
{
	for (GLuint i = 0; i < 2; ++i)
	{
		glCreateFramebuffers(1, &dualFrameBuffers[i]);
		glCreateTextures(GL_TEXTURE_2D, 1, &dualColorBuffers[i]);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(dualColorBuffers[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureStorage2D(dualColorBuffers[i], 1, GL_RGBA, windowWidth, windowHeight);
		glTextureSubImage2D(dualColorBuffers[i], 0, 0, 0, windowWidth, windowHeight, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glNamedFramebufferTexture(dualFrameBuffers[i], GL_COLOR_ATTACHMENT0, dualColorBuffers[i], 0);
	}
}

GLuint& FrameBuffer::getMultiBuffer(const size_t bufferIndex)
{
	return dualFrameBuffers[bufferIndex];
}

GLuint& FrameBuffer::getDualColorBuffer(const size_t bufferIndex)
{
	return dualColorBuffers[bufferIndex];
}

const GLuint& FrameBuffer::getFrameBuffer() const
{
	return frameBuffer;
}

const GLuint& FrameBuffer::getColorBuffer() const
{
	return colorBuffer;
}