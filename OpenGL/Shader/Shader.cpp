#include "Shader.h"

Shader::Shader() : programID(0),
				   positionsVBO(0),
				   colorsVBO(0),
				   textureCoordinatesVBO(0),
				   vertexArrayObject(0),
				   elementBufferObject(0) {}

Shader::~Shader()
{
	glUseProgram(0);
	glDeleteProgram(programID);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	glDeleteBuffers(1, &positionsVBO);
	glDeleteBuffers(1, &colorsVBO);
	glDeleteBuffers(1, &textureCoordinatesVBO);
	glDeleteBuffers(1, &elementBufferObject);
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Shader::loadFromFile(const std::string& vertextShaderFile, const std::string& fragmentShaderFile)
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
}

const GLuint& Shader::getProgramID() const
{
	return programID;
}

const GLuint& Shader::getVertexArrayObject() const
{
	return vertexArrayObject;
}

// update the vertex buffer object with the vertices of 2 swapped rectangles.  the indices correspond to the rectangles that have
// already been swapped in the rectangleVertices vector.  not every sort swaps rectangles that are next to each other, thus the need
// for the 2 indices
void Shader::updateVertexBuffer(const std::pair<size_t, size_t>& indexOfSwap, const std::vector<glm::vec2>& rectangleVertices)
{
	if (indexOfSwap.second == indexOfSwap.first + verticesPerRectangle) // if we're updating one continuous range we only need 1 glNamedBufferSubData call
	{
		glNamedBufferSubData(positionsVBO, indexOfSwap.first * sizeof(glm::vec2), (verticesPerRectangle * 2) * sizeof(glm::vec2), &rectangleVertices.at(indexOfSwap.first));
	}
	else
	{
		glNamedBufferSubData(positionsVBO, indexOfSwap.first * sizeof(glm::vec2), verticesPerRectangle * sizeof(glm::vec2), &rectangleVertices.at(indexOfSwap.first));
		glNamedBufferSubData(positionsVBO, indexOfSwap.second * sizeof(glm::vec2), verticesPerRectangle * sizeof(glm::vec2), &rectangleVertices.at(indexOfSwap.second));
	}
	

	//waitBuffer();

	/*
	for (size_t i = 0; i < verticesPerRectangle; ++i)
	{
		vertexBufferPtr[syncRanges[syncRangeIndex].startIndex + indexOfSwap.first + i] = rectangleVertices.at(indexOfSwap.first + i);
		vertexBufferPtr[syncRanges[syncRangeIndex].startIndex + indexOfSwap.second + i] = rectangleVertices.at(indexOfSwap.second + i);
	}
	*/

	/*
	for (size_t i = 0; i != rectangleVertices.size(); ++i)
	{
		vertexBufferPtr[i + syncRanges[syncRangeIndex].startIndex] = rectangleVertices.at(i);
	}
	*/
//	lockBuffer(syncRanges[syncRangeIndex].sync);
}

// update the vertex buffer object with the vertices of just one single rectangle
void Shader::updateVertexBuffer(const size_t indexOfUpdate, const std::vector<glm::vec2>& rectangleVertices) const
{
	glNamedBufferSubData(positionsVBO, indexOfUpdate * sizeof(glm::vec2), glm::vec2::length() * sizeof(glm::vec2), &rectangleVertices.at(indexOfUpdate));
}

template <typename T>
void Shader::createBuffers(const GLenum usageFlag, 
						   const std::vector<glm::vec2>& vertexPositions, 
						   const std::vector<glm::u8vec3>& vertexColors, 
						   const std::vector<T>& vertexIndices, 
						   const std::vector<glm::vec2>* textureCoordinates)
{
	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(1, &positionsVBO);
	glGenBuffers(1, &colorsVBO);
	glGenBuffers(1, &elementBufferObject);

	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(glm::vec2), vertexPositions.data(), usageFlag);
	glVertexAttribPointer(0, glm::vec2::length(), GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, vertexColors.size() * sizeof(glm::u8vec3), vertexColors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, glm::u8vec3::length(), GL_UNSIGNED_BYTE, GL_TRUE, glm::u8vec3::length() * sizeof(GLubyte), (void*)0);
	glEnableVertexAttribArray(1);

	if (textureCoordinates)
	{
		glGenBuffers(1, &textureCoordinatesVBO);
		glBindBuffer(GL_ARRAY_BUFFER, textureCoordinatesVBO);
		glBufferData(GL_ARRAY_BUFFER, textureCoordinates->size() * sizeof(glm::vec2), textureCoordinates->data(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, glm::vec2::length(), GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
		glEnableVertexAttribArray(2);
	}

	GLsizeiptr indexTypeSize = std::is_same_v<T, GLushort> ? vertexIndices.size() * sizeof(GLushort) : vertexIndices.size() * sizeof(GLubyte);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexTypeSize, vertexIndices.data(), GL_STATIC_DRAW);
}

template void Shader::createBuffers<GLushort>(const GLenum, const std::vector<glm::vec2>&, const std::vector<glm::u8vec3>&, const std::vector<GLushort>&, const std::vector<glm::vec2>*);
template void Shader::createBuffers<GLubyte>(const GLenum, const std::vector<glm::vec2>&, const std::vector<glm::u8vec3>&, const std::vector<GLubyte>&, const std::vector<glm::vec2>*);

void Shader::createPersistentBuffer(const std::vector<glm::vec2>& vertexPositions, const std::vector<glm::u8vec3>& vertexColors, const std::vector<GLushort>& vertexIndices)
{
	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(1, &positionsVBO);
	glGenBuffers(1, &colorsVBO);
	glGenBuffers(1, &elementBufferObject);

	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glVertexAttribPointer(0, glm::vec2::length(), GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(0);

	size_t tripleBufferSize = numberOfRectangles * verticesPerRectangle * sizeof(glm::vec2) * 3;

	glBufferStorage(GL_ARRAY_BUFFER, tripleBufferSize, vertexPositions.data(), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
	vertexBufferPtr = (glm::vec2*)glMapBufferRange(GL_ARRAY_BUFFER, 0, tripleBufferSize, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

	syncRanges[0].startIndex = 0;
	syncRanges[1].startIndex = numberOfRectangles * verticesPerRectangle;
	syncRanges[2].startIndex = numberOfRectangles * verticesPerRectangle * 2;

	/*
	for (size_t i = 0; i < vertexPositions.size(); ++i)
	{
		vertexBufferPtr[syncRanges[1].startIndex + i] = vertexPositions.at(i);
		vertexBufferPtr[syncRanges[2].startIndex + i] = vertexPositions.at(i);
	}
	*/

	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, vertexColors.size() * sizeof(glm::u8vec3), vertexColors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, glm::u8vec3::length(), GL_UNSIGNED_BYTE, GL_TRUE, glm::u8vec3::length() * sizeof(GLubyte), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(GLushort), vertexIndices.data(), GL_STATIC_DRAW);	
}

void Shader::createBufferNew(const std::vector<glm::vec2>& vertexPositions, const std::vector<glm::u8vec3>& vertexColors, const std::vector<GLushort>& vertexIndices)
{
	glCreateBuffers(1, &positionsVBO);
	glNamedBufferData(positionsVBO, vertexPositions.size() * sizeof(glm::vec2), vertexPositions.data(), GL_DYNAMIC_DRAW);

	glCreateBuffers(1, &colorsVBO);
	glNamedBufferData(colorsVBO, vertexColors.size() * sizeof(glm::u8vec3), vertexColors.data(), GL_STATIC_DRAW);

	glCreateBuffers(1, &elementBufferObject);
	glNamedBufferData(elementBufferObject, vertexIndices.size() * sizeof(GLushort), vertexIndices.data(), GL_STATIC_DRAW);

	glCreateVertexArrays(1, &vertexArrayObject);
	glVertexArrayVertexBuffer(vertexArrayObject, 0, positionsVBO, 0, sizeof(glm::vec2));
	glVertexArrayVertexBuffer(vertexArrayObject, 1, colorsVBO, 0, sizeof(glm::u8vec3));
	glVertexArrayElementBuffer(vertexArrayObject, elementBufferObject);

	glEnableVertexArrayAttrib(vertexArrayObject, 0);
	glEnableVertexArrayAttrib(vertexArrayObject, 1);

	glVertexArrayAttribFormat(vertexArrayObject, 0, glm::vec2::length(), GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(vertexArrayObject, 1, glm::u8vec3::length(), GL_UNSIGNED_BYTE, GL_TRUE, 0);

	glVertexArrayAttribBinding(vertexArrayObject, 0, 0);
	glVertexArrayAttribBinding(vertexArrayObject, 1, 1);
}

GLuint Shader::compileShader(const GLenum& shaderType, const std::string& shaderSource) const
{
	GLuint shaderID = glCreateShader(shaderType);
	const char* sourceToCompile = shaderSource.c_str();

	glShaderSource(shaderID, 1, &sourceToCompile, nullptr);
	glCompileShader(shaderID);

	return shaderID;
}

void Shader::waitBuffer()
{
	if (syncRanges[syncRangeIndex].sync)
	{
		while (1)
		{
			GLenum waitReturn = glClientWaitSync(syncRanges[syncRangeIndex].sync, GL_SYNC_FLUSH_COMMANDS_BIT, 1);
			if (waitReturn == GL_ALREADY_SIGNALED || waitReturn == GL_CONDITION_SATISFIED)
				return;
		}
	}
}

void Shader::lockBuffer()
{
	if (syncRanges[syncRangeIndex].sync)
		glDeleteSync(syncRanges[syncRangeIndex].sync);

	syncRanges[syncRangeIndex].sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	syncRangeIndex = (1 + syncRangeIndex) % 3;
}