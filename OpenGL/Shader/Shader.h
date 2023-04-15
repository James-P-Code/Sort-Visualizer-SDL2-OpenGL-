#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <type_traits>
#include "../Constants.h"

class Shader final
{
public:
	Shader();
	~Shader();
	void loadFromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	const GLuint& getProgramID() const;
	const GLuint& getVertexArrayObject() const;
	void updateVertexBuffer(const std::pair<size_t, size_t>& indexOfSwap, const std::vector<glm::vec2>& rectangleVertices);
	void updateVertexBuffer(const size_t indexToUpdate, const std::vector<glm::vec2>& rectangleVertices) const;
	template <typename T> void createBuffers(const GLenum usageFlag,
										     const std::vector<glm::vec2>& vertexPositions,
										     const std::vector<glm::u8vec3>& vertexColors, 
								             const std::vector<T>& vertexIndices,
									         const std::vector<glm::vec2>* textureCoordinates = nullptr);
	void createPersistentMappedBuffer(const std::vector<glm::vec2>&, const std::vector<glm::u8vec3>&, const std::vector<GLushort>&);
	void createMultipleBuffers(const std::vector<glm::vec2>&, const std::vector<glm::u8vec3>&, const std::vector<GLushort>&);
	void createSingleBuffer(const std::vector<glm::vec2>&, const std::vector<glm::u8vec3>&, const std::vector<GLubyte>&, const std::vector<glm::vec2>&);
	void waitBuffer();
	void lockBuffer();
	const size_t getBufferStart() const;
	void updateBufferStart();

private:
	static constexpr int persistentBufferSize = 3;
	GLuint programID, positionsVBO, colorsVBO, textureCoordinatesVBO, vertexArrayObject, elementBufferObject;
	glm::vec2* vertexBufferData = nullptr;

	struct BufferRange
	{
		size_t startIndex = 0;
		GLsync sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	};

	BufferRange bufferRanges[3];
	size_t syncRangeIndex = 0;

	GLuint compileShader(const GLenum& shaderType, const std::string& shaderSource) const;
};