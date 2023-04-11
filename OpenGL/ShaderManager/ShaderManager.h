#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Constants.h"

class BarChart;

class ShaderManager final
{
public:
	~ShaderManager();
	void loadFromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	const GLuint& getProgramID() const;
	const GLuint& getVertexArrayObject() const;
	//template <typename V, typename C, typename I> void createBuffers(const std::vector<V>* vertexPositions, const std::vector<C>* vertexColors, const std::vector<I>* vertexIndices = nullptr);
	void updateVertexBuffer(const std::pair<size_t, size_t>& indexOfSwap, const std::vector<glm::vec2>& rectangleVertices) const;
	void updateVertexBuffer(const size_t indexToUpdate, const std::vector<glm::vec2>& rectangleVertices) const;

private:
	GLuint programID = 0, vertexVBO = 0, colorVBO = 0, vertexArrayObject = 0, elementBufferObject = 0;

	GLuint compileShader(const GLenum& shaderType, const std::string& shaderSource) const;
	void createBuffers(BarChart& barChart);

public:

	template <typename V, typename C, typename I>
	void createBuffers(const std::vector<V>* vertexPositions, const std::vector<C>* vertexColors, const std::vector<I>* vertexIndices = nullptr)
	{
		glGenVertexArrays(1, &vertexArrayObject);
		glGenBuffers(1, &vertexVBO);
		glGenBuffers(1, &colorVBO);
		if (vertexIndices)
		{
			glGenBuffers(1, &elementBufferObject);
		}

		glBindVertexArray(vertexArrayObject);

		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, vertexPositions->size() * sizeof(V), vertexPositions->data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, V::length(), GL_FLOAT, GL_FALSE, sizeof(V), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferData(GL_ARRAY_BUFFER, vertexColors->size() * sizeof(C), vertexColors->data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, C::length(), GL_UNSIGNED_BYTE, GL_TRUE, C::length() * sizeof(GLubyte), (void*)0);

		if (vertexIndices)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices->size() * sizeof(I), vertexIndices->data(), GL_STATIC_DRAW);
		}

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}
};