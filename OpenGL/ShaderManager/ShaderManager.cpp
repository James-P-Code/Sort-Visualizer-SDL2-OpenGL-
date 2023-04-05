#include "ShaderManager.h"
#include "../BarChart/BarChart.h"

ShaderManager::~ShaderManager()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &elementBufferObject);
	glDeleteProgram(programID);
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

	bindObjects(barChart);
}

GLuint ShaderManager::compileShader(const GLenum& shaderType, const std::string& shaderSource)
{
	GLuint shaderID = glCreateShader(shaderType);
	const char* sourceToCompile = shaderSource.c_str();

	glShaderSource(shaderID, 1, &sourceToCompile, nullptr);
	glCompileShader(shaderID);

	return shaderID;
}

const GLuint& ShaderManager::getProgram() const
{
	return programID;
}

const GLuint& ShaderManager::getVertexArrayObject() const
{
	return vertexArrayObject;
}

void ShaderManager::bindObjects(BarChart& barChart)
{
	constexpr GLint floatsPerVertex = 2, floatsPerColor = 3;

	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &elementBufferObject);

	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, barChart.getRectangleVertices().size() * sizeof(GLfloat), barChart.getRectangleVertices().data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(GLfloat), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, barChart.getVertexColors().size() * sizeof(GLfloat), barChart.getVertexColors().data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, floatsPerColor * sizeof(GLfloat), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, barChart.getIndices().size() * sizeof(GLushort), barChart.getIndices().data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	verticesToDraw = static_cast<GLsizei>(barChart.getRectangleVertices().size());
	primitiveMode = GL_TRIANGLES;
}

const GLenum& ShaderManager::getPrimitiveMode() const
{
	return primitiveMode;
}

const GLsizei& ShaderManager::getVerticesCount() const
{
	return verticesToDraw;
}

void ShaderManager::updateVertexBuffer(const int index, const std::vector<GLfloat>& swaps) const
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(GLfloat), swaps.size() * sizeof(GLfloat), swaps.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}