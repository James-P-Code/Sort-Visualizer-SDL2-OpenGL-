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
	void updateVertexBuffer(const std::pair<size_t, size_t>& indexOfSwap, const std::vector<glm::vec2>& rectangleVertices) const;
	void updateVertexBuffer(const size_t indexToUpdate, const std::vector<glm::vec2>& rectangleVertices) const;
	template <typename T> void createBuffers(const GLenum usageFlag,
										     const std::vector<glm::vec2>& vertexPositions,
										     const std::vector<glm::u8vec3>& vertexColors, 
								             const std::vector<T>& vertexIndices,
									         const std::vector<glm::vec2>* textureCoordinates = nullptr);

private:
	GLuint programID, positionsVBO, colorsVBO, textureCoordinatesVBO, vertexArrayObject, elementBufferObject;

	GLuint compileShader(const GLenum& shaderType, const std::string& shaderSource) const;
};