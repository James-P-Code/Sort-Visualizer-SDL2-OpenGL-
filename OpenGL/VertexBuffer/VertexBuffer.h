#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "../Constants.h"

class VertexBuffer final
{
public:
	VertexBuffer();
	~VertexBuffer();
	void createSingleBuffer(const std::vector<glm::vec2>&, const std::vector<glm::u8vec3>&, const std::vector<GLubyte>&, const std::vector<glm::vec2>&);
	void createPersistentMappedBuffer(const std::vector<glm::vec2>&, const std::vector<glm::u8vec3>&, const std::vector<GLushort>&);
	void createScreenSpaceBuffer(const std::vector<glm::vec2>&, const std::vector<glm::vec2>&, const std::vector<GLubyte>&);
	const GLuint& getVertexArray() const;
	const size_t getBufferDataStartIndex() const;
	void update(const std::vector<glm::vec2>&);
	void lock();

private:
	static constexpr int persistentBufferSize = 3;
	GLuint positionsVBO, colorsVBO, textureCoordinatesVBO, indicesEBO, vertexArray;
	size_t syncRangeIndex;
	glm::vec2* vertexBufferData;
	struct BufferRange
	{
		size_t startIndex = 0;
		GLsync sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	};
	BufferRange bufferRanges[persistentBufferSize];

	void wait();
};