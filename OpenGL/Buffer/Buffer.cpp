#include "Buffer.h"

Buffer::Buffer() : positionsVBO(0),
				   colorsVBO(0),
				   textureCoordinatesVBO(0),
				   indicesEBO(0),
				   vertexArray(0),
				   syncRangeIndex(0) {}

Buffer::~Buffer()
{
	glUnmapNamedBuffer(positionsVBO);
	glUnmapNamedBuffer(colorsVBO);
	glUnmapNamedBuffer(textureCoordinatesVBO);
	glUnmapNamedBuffer(indicesEBO);
	glDeleteBuffers(1, &positionsVBO);
	glDeleteBuffers(1, &colorsVBO);
	glDeleteBuffers(1, &textureCoordinatesVBO);
	glDeleteBuffers(1, &indicesEBO);
	glDeleteVertexArrays(1, &vertexArray);
}

void Buffer::createSingleBuffer(const std::vector<glm::vec2>& vertexPositions,
								const std::vector<glm::u8vec3>& vertexColors,
								const std::vector<GLubyte>& vertexIndices,
								const std::vector<glm::vec2>& textureCoordinates)
{
	constexpr int positionsBindingIndex = 0, colorsBindingIndex = 1, textureCoordinatesBindingIndex = 2;
	constexpr int positionsLayoutIndex = 0, colorsLayoutIndex = 1, textureCoordinatesLayoutIndex = 2;

	glCreateBuffers(1, &positionsVBO);
	// the layout of the buffer is:  [PPPPCCCCTTTT], where P = position, C = color, T = texture coordinate
	// the size of the buffers equals the size of the positions, colors and texture coordinates.  the positions and texture coordinates are both the same data type, thus the "* 2"
	glNamedBufferStorage(positionsVBO, vertexPositions.size() * sizeof(glm::vec2) * 2 + vertexColors.size() * sizeof(glm::u8vec3) + textureCoordinates.size(), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(positionsVBO, 0, vertexPositions.size() * sizeof(glm::vec2), vertexPositions.data());  // positions
	glNamedBufferSubData(positionsVBO, vertexPositions.size() * sizeof(glm::vec2), vertexColors.size() * sizeof(glm::u8vec3), vertexColors.data());  // colors
	glNamedBufferSubData(positionsVBO, vertexPositions.size() * sizeof(glm::vec2) + vertexColors.size() * sizeof(glm::u8vec3), textureCoordinates.size() * sizeof(glm::vec2), textureCoordinates.data());  // texture coords

	glCreateBuffers(1, &indicesEBO);
	glNamedBufferStorage(indicesEBO, vertexIndices.size() * sizeof(GLubyte), vertexIndices.data(), GL_MAP_READ_BIT);

	glCreateVertexArrays(1, &vertexArray);
	glVertexArrayVertexBuffer(vertexArray, positionsBindingIndex, positionsVBO, 0, sizeof(glm::vec2));
	glVertexArrayVertexBuffer(vertexArray, colorsBindingIndex, positionsVBO, vertexPositions.size() * sizeof(glm::vec2), sizeof(glm::u8vec3));
	glVertexArrayVertexBuffer(vertexArray, textureCoordinatesBindingIndex, positionsVBO, vertexPositions.size() * sizeof(glm::vec2) + vertexColors.size() * sizeof(glm::u8vec3), sizeof(glm::vec2));
	glVertexArrayElementBuffer(vertexArray, indicesEBO);

	glEnableVertexArrayAttrib(vertexArray, positionsLayoutIndex);
	glEnableVertexArrayAttrib(vertexArray, colorsLayoutIndex);
	glEnableVertexArrayAttrib(vertexArray, textureCoordinatesLayoutIndex);

	glVertexArrayAttribFormat(vertexArray, positionsLayoutIndex, glm::vec2::length(), GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(vertexArray, colorsLayoutIndex, glm::u8vec3::length(), GL_UNSIGNED_BYTE, GL_TRUE, 0);
	glVertexArrayAttribFormat(vertexArray, textureCoordinatesLayoutIndex, glm::vec2::length(), GL_FLOAT, GL_FALSE, 0);

	glVertexArrayAttribBinding(vertexArray, positionsLayoutIndex, positionsBindingIndex);
	glVertexArrayAttribBinding(vertexArray, colorsLayoutIndex, colorsBindingIndex);
	glVertexArrayAttribBinding(vertexArray, textureCoordinatesLayoutIndex, textureCoordinatesBindingIndex);
}

void Buffer::createPersistentMappedBuffer(const std::vector<glm::vec2>& vertexPositions, const std::vector<glm::u8vec3>& vertexColors, const std::vector<GLushort>& vertexIndices)
{
	constexpr size_t firstBuffer = 0, secondBuffer = 1, thirdBuffer = 2;
	constexpr GLuint positionBindingIndex = 0, colorBindingIndex = 1;
	constexpr GLuint positionLayoutIndex = 0, colorLayoutIndex = 1;
	constexpr int tripleBuffer = 3;
	GLsizeiptr bufferSize = numberOfRectangles * verticesPerRectangle * sizeof(glm::vec2) * tripleBuffer;

	// create vertex buffer for the positions of the vertices
	glCreateBuffers(1, &positionsVBO);
	glNamedBufferStorage(positionsVBO, bufferSize, vertexPositions.data(), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
	// map the buffer
	vertexBufferData = (glm::vec2*)glMapNamedBufferRange(positionsVBO, 0, bufferSize, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

	bufferRanges[firstBuffer].startIndex = 0;
	bufferRanges[secondBuffer].startIndex = numberOfRectangles * verticesPerRectangle;
	bufferRanges[thirdBuffer].startIndex = numberOfRectangles * verticesPerRectangle * 2;

	// fill up the buffer "ranges" with the position data (note the first range was already filled during the glNamedBufferStorage call above)
	for (size_t i = 0; i < vertexPositions.size(); ++i)
	{
		vertexBufferData[bufferRanges[secondBuffer].startIndex + i] = vertexPositions.at(i);
		vertexBufferData[bufferRanges[thirdBuffer].startIndex + i] = vertexPositions.at(i);
	}

	glCreateBuffers(1, &colorsVBO);
	glNamedBufferStorage(colorsVBO, vertexColors.size() * sizeof(glm::u8vec3), vertexColors.data(), GL_MAP_READ_BIT);

	glCreateBuffers(1, &indicesEBO);
	glNamedBufferStorage(indicesEBO, vertexIndices.size() * sizeof(GLushort), vertexIndices.data(), GL_MAP_READ_BIT);

	glCreateVertexArrays(1, &vertexArray);
	glVertexArrayVertexBuffer(vertexArray, positionBindingIndex, positionsVBO, 0, sizeof(glm::vec2));
	glVertexArrayVertexBuffer(vertexArray, colorBindingIndex, colorsVBO, 0, sizeof(glm::u8vec3));
	glVertexArrayElementBuffer(vertexArray, indicesEBO);

	glEnableVertexArrayAttrib(vertexArray, positionLayoutIndex);
	glEnableVertexArrayAttrib(vertexArray, colorLayoutIndex);

	glVertexArrayAttribFormat(vertexArray, positionLayoutIndex, glm::vec2::length(), GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(vertexArray, colorLayoutIndex, glm::u8vec3::length(), GL_UNSIGNED_BYTE, GL_TRUE, 0);

	glVertexArrayAttribBinding(vertexArray, positionLayoutIndex, positionBindingIndex);
	glVertexArrayAttribBinding(vertexArray, colorLayoutIndex, colorBindingIndex);
}

const GLuint& Buffer::getVertexArray() const
{
	return vertexArray;
}

const size_t Buffer::getBufferDataStartIndex() const
{
	return bufferRanges[syncRangeIndex].startIndex;
}

void Buffer::update(const std::vector<glm::vec2>& rectangleVertices)
{
	wait();

	for (size_t i = 0; i != rectangleVertices.size(); ++i)
	{
		vertexBufferData[i + bufferRanges[syncRangeIndex].startIndex] = rectangleVertices.at(i);
	}
}

void Buffer::lock()
{
	glDeleteSync(bufferRanges[syncRangeIndex].sync);
	bufferRanges[syncRangeIndex].sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	syncRangeIndex = ++syncRangeIndex % persistentBufferSize;
}

void Buffer::wait()
{
	GLenum waitReturn = glClientWaitSync(bufferRanges[syncRangeIndex].sync, GL_SYNC_FLUSH_COMMANDS_BIT, 1);
	while (waitReturn != GL_ALREADY_SIGNALED && waitReturn != GL_CONDITION_SATISFIED)
	{
		waitReturn = glClientWaitSync(bufferRanges[syncRangeIndex].sync, GL_SYNC_FLUSH_COMMANDS_BIT, 1);
	}
}