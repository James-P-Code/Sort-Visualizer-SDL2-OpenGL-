#include "ShaderManager.h"
#include "../BarChart/BarChart.h"

ShaderManager::~ShaderManager()
{
	glUseProgram(0);
	glDeleteProgram(programID);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &elementBufferObject);
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void ShaderManager::loadShader(const std::string& vertextShaderFile, const std::string& fragmentShaderFile, BarChart& barChart)
{
	std::ifstream vertexFile(vertextShaderFile);
	std::ifstream fragmentFile(fragmentShaderFile);
	std::string vertexSource, fragmentSource;

	if (vertexFile && fragmentFile)
	{
		vertexSource.assign((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
		fragmentSource.assign((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());
	}
	else
	{
		std::cout << "Error loading shader file!\n";
	}

	GLuint vertexShaderID = compileShader(GL_VERTEX_SHADER, vertexSource);
	GLuint fragmentShaderID = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	createBuffers(barChart);
}

GLuint ShaderManager::compileShader(const GLenum& shaderType, const std::string& shaderSource) const
{
	GLuint shaderID = glCreateShader(shaderType);
	const char* sourceToCompile = shaderSource.c_str();

	glShaderSource(shaderID, 1, &sourceToCompile, nullptr);
	glCompileShader(shaderID);

	return shaderID;
}

const GLuint& ShaderManager::getProgramID() const
{
	return programID;
}

const GLuint& ShaderManager::getVertexArrayObject() const
{
	return vertexArrayObject;
}

void ShaderManager::createBuffers(BarChart& barChart)
{
	constexpr GLint floatsPerVertex = 2, bytesPerColor = 3;

	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &elementBufferObject);

	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, barChart.getRectangleVertices().size() * sizeof(GLfloat), barChart.getRectangleVertices().data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(GLfloat), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, barChart.getVertexColors().size() * sizeof(GLubyte), barChart.getVertexColors().data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, bytesPerColor, GL_UNSIGNED_BYTE, GL_TRUE, bytesPerColor * sizeof(GLubyte), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, barChart.getIndices().size() * sizeof(GLushort), barChart.getIndices().data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	verticesToDraw = static_cast<GLsizei>(barChart.getRectangleVertices().size());
}

const GLsizei& ShaderManager::getVerticesCount() const
{
	return verticesToDraw;
}

// update the vertex buffer object with the vertices of 2 swapped rectangles.  the indices correspond to the rectangles that have
// already been swapped in the rectangleVertices vector.  not every sort swaps rectangles that are next to each other, thus the need
// for the 2 indices
void ShaderManager::updateVertexBuffer(const std::pair<size_t, size_t>& indexOfSwap, const std::vector<GLfloat>& rectangleVertices) const
{
	constexpr int floatsPerRectangle = 8;

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	// if we're updating one continuous range we only need 1 glBufferSubData call
	if (indexOfSwap.second == indexOfSwap.first + floatsPerRectangle)
	{
		glBufferSubData(GL_ARRAY_BUFFER, indexOfSwap.first * sizeof(GLfloat), (floatsPerRectangle * 2) * sizeof(GLfloat), &rectangleVertices.at(indexOfSwap.first));
	}
	else
	{
		glBufferSubData(GL_ARRAY_BUFFER, indexOfSwap.first * sizeof(GLfloat), floatsPerRectangle * sizeof(GLfloat), &rectangleVertices.at(indexOfSwap.first));
		glBufferSubData(GL_ARRAY_BUFFER, indexOfSwap.second * sizeof(GLfloat), floatsPerRectangle * sizeof(GLfloat), &rectangleVertices.at(indexOfSwap.second));
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}