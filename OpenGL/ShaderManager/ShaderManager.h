#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

class BarChart;

class ShaderManager final
{
public:
	~ShaderManager();
	void loadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile, BarChart& barChart);
	const GLuint& getProgramID() const;
	const GLuint& getVertexArrayObject() const;
	const GLsizei& getVerticesCount() const;
	void updateVertexBuffer(const std::pair<size_t, size_t>&, const std::vector<GLfloat>&) const;

private:
	GLuint programID = 0, vertexVBO = 0, colorVBO = 0, vertexArrayObject = 0, elementBufferObject = 0;
	GLsizei verticesToDraw = 0;

	GLuint compileShader(const GLenum& shaderType, const std::string& shaderSource) const;
	void createBuffers(BarChart& barChart);
};