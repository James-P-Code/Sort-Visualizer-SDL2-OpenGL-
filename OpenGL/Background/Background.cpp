#include "Background.h"

Background::Background()
{
	constexpr float byteMultiplier = 255.0f;
	std::vector<glm::vec2> vertexPositions;
	std::vector<glm::u8vec3> vertexColors;
	std::vector<GLubyte> vertexIndices;
	std::vector<glm::vec2> textureCoordinates;
	int imageWidth, imageHeight, nrChannels;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	imageData = stbi_load("background.jpg", &imageWidth, &imageHeight, &nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData);

	vertexPositions.push_back(glm::vec2(-1.0f, 1.0f));
	vertexPositions.push_back(glm::vec2(1.0f, 1.0f));
	vertexPositions.push_back(glm::vec2(1.0f, -1.0f));
	vertexPositions.push_back(glm::vec2(-1.0f, -1.0f));

	vertexColors.push_back(glm::u8vec3(std::round(1.0f * byteMultiplier), std::round(0.0f * byteMultiplier), std::round(0.0f * byteMultiplier)));
	vertexColors.push_back(glm::u8vec3(std::round(0.0f * byteMultiplier), std::round(1.0f * byteMultiplier), std::round(0.0f * byteMultiplier)));
	vertexColors.push_back(glm::u8vec3(std::round(0.0f * byteMultiplier), std::round(0.0f * byteMultiplier), std::round(1.0f * byteMultiplier)));
	vertexColors.push_back(glm::u8vec3(std::round(1.0f * byteMultiplier), std::round(1.0f * byteMultiplier), std::round(0.0f * byteMultiplier)));

	vertexIndices.push_back(0);
	vertexIndices.push_back(1);
	vertexIndices.push_back(2);
	vertexIndices.push_back(2);
	vertexIndices.push_back(3);
	vertexIndices.push_back(0);

	textureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
	textureCoordinates.push_back(glm::vec2(1.0f, 1.0f));
	textureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
	textureCoordinates.push_back(glm::vec2(0.0f, 0.0f));

	shader.loadFromFile("background.vert", "background.frag");
	shader.createBuffers(GL_STATIC_DRAW, vertexPositions, vertexColors, vertexIndices, &textureCoordinates);
}

void Background::draw() const
{
	glUseProgram(shader.getProgramID());
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(shader.getVertexArrayObject());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}