#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include "../Constants.h"

class BarChart final
{
public:
	BarChart();
	const std::vector<glm::vec2>& getRectangleVertices() const;
	const std::vector<glm::u8vec3>& getVertexColors() const;
	const std::vector<GLushort>& getIndices() const;
	void swapRectangles(const std::pair<size_t, size_t>& indexOfSwap);
	void updateRectangle(const size_t, const glm::vec2&);

private:
	std::vector<glm::vec2> rectangleVertices;
	std::vector<glm::u8vec3> vertexColors;
	std::vector<GLushort> vertexIndices; // the indices used for the element buffer

	const GLfloat normalize(const float& numberToNormalize) const;
};