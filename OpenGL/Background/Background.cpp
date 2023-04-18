#include "Background.h"

Background::Background()
{
	constexpr float byteMultiplier = 255.0f;
	std::vector<glm::vec2> vertexPositions;
	std::vector<glm::u8vec3> vertexColors;
	std::vector<GLubyte> vertexIndices;
	std::vector<glm::vec2> textureCoordinates;
	int imageWidth, imageHeight, imageChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* imageData = stbi_load("background.jpg", &imageWidth, &imageHeight, &imageChannels, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &texture);

	glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureStorage2D(texture, 1, GL_RGB8, imageWidth, imageHeight);
	glTextureSubImage2D(texture, 0, 0, 0, imageWidth, imageHeight, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glGenerateTextureMipmap(texture);

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

	backgroundImageShader.loadFromFile("background.vert", "background.frag");
	backgroundImageVertexBuffer.createSingleBuffer(vertexPositions, vertexColors, vertexIndices, textureCoordinates);
}

void Background::draw()
{
	backgroundImageShader.useProgram();
	glBindTextureUnit(0, texture);
	glBindVertexArray(backgroundImageVertexBuffer.getVertexArray());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
	glBindVertexArray(0);
}