#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include "../RenderObject/RenderObject.h"
#include "../Constants.h"

class BarChart final : public RenderObject
{
public:
	BarChart();
	void draw() override;
	const std::vector<glm::vec2>& getVertexPositions() const;
	const std::vector<glm::u8vec3>& getVertexColors() const;
	const std::vector<GLushort>& getIndices() const;
	void swapRectangles(const std::pair<size_t, size_t>& indexOfSwap);
	void updateRectangle(const size_t, const glm::vec2&);
	void setRectangleToHighlight(const int);

private:
	glm::mat4 barChartModelMatrix = glm::mat4(1.0f); // the model matrix for the bar chart
	VertexBuffer barChartVertexBuffer;
	Shader barChartShader;
	Shader highlightShader;
	VertexBuffer screenSpaceVertexBuffer;
	Shader screenSpaceShader;
	std::vector<glm::vec2> vertexPositions;
	std::vector<glm::u8vec3> vertexColors;
	std::vector<GLushort> vertexIndices; // the indices used for the element buffer
	int rectangleToHighlight; 
	int barChartHighlightUniformLocation, barChartProjectionUniformLocation, barChartModelUniformLocation; // the locations of uniform variables of the bar chart shader
	int highlightProjectionUniformLocation, highlightModelUniformLocation, highlightTimeUniformLocation;
	Uint32 time;

	const GLfloat normalize(const float& numberToNormalize) const;
};