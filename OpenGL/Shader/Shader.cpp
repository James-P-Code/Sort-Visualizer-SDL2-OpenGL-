#include "Shader.h"

Shader::Shader() : programID(0) {}

Shader::~Shader()
{
	glUseProgram(0);
	glDeleteProgram(programID);
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
	getUniformsAndLocations();

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

const GLuint& Shader::getProgramID() const
{
	return programID;
}

void Shader::useProgram() const
{
	glUseProgram(programID);
}

void Shader::setUniformInt(const std::string& uniformName, const GLint valueToSet) const
{
	glUniform1i(uniforms.at(uniformName), valueToSet);
}

void Shader::setUniformMatrix4f(const std::string& uniformName, const GLfloat* valueToSet) const
{
	glUniformMatrix4fv(uniforms.at(uniformName), 1, GL_FALSE, valueToSet);
}

void Shader::setUniformFloat(const std::string& uniformName, const GLfloat valueToSet) const
{
	glUniform1f(uniforms.at(uniformName), valueToSet);
}

GLuint Shader::compileShader(const GLenum& shaderType, const std::string& shaderSource) const
{
	constexpr GLsizei infoSize = 512;
	char infoLog[infoSize];
	GLint compilationSuccess;
	GLuint shaderID = glCreateShader(shaderType);
	const char* sourceToCompile = shaderSource.c_str();

	glShaderSource(shaderID, 1, &sourceToCompile, nullptr);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationSuccess);
	if (!compilationSuccess)
	{
		glGetProgramInfoLog(shaderID, infoSize, NULL, infoLog);
		std::cout << "Shader Compilation Error!\n" << infoLog << '\n';
	}

	return shaderID;
}

void Shader::getUniformsAndLocations()
{
	GLint numberOfUniforms, maxUniformNameLength, currentUniformLength, currentUniformSize;
	GLenum uniformType;

	glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &numberOfUniforms);
	glGetProgramiv(programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformNameLength);

	std::unique_ptr<char[]> uniformName = std::make_unique<char[]>(maxUniformNameLength);

	if (numberOfUniforms > 0)
	{
		for (GLint i = 0; i < numberOfUniforms; ++i)
		{
			glGetActiveUniform(programID, i, maxUniformNameLength, &currentUniformLength, &currentUniformSize, &uniformType, uniformName.get());
			uniforms[std::string(uniformName.get(), currentUniformLength)] = glGetUniformLocation(programID, uniformName.get());		
		}
	}
}