#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>

class Shader final
{
public:
	Shader();
	~Shader();
	void loadFromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	const GLuint& getProgramID() const;
	void useProgram() const;

private:
	GLuint programID;

	GLuint compileShader(const GLenum& shaderType, const std::string& shaderSource) const;
};