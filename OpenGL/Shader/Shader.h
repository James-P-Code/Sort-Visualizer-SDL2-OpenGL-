#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <memory>

class Shader final
{
public:
	Shader();
	~Shader();
	void loadFromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	const GLuint& getProgramID() const;
	void useProgram() const;
	void setUniformInt(const std::string&, const GLint) const;
	void setUniformMatrix4f(const std::string&, const GLfloat* valueToSet) const;
	void setUniformFloat(const std::string&, const GLfloat) const;

private:
	GLuint programID;
	std::unordered_map<std::string, GLint> uniforms;

	GLuint compileShader(const GLenum& shaderType, const std::string& shaderSource) const;
	void getUniformsAndLocations();
};