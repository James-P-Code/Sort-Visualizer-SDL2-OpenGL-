#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <array>
#include <vector>
#include <algorithm>
#include <random>

class BarChart final
{
public:
	BarChart();
	const std::vector<GLfloat>& getRectangleVertices() const;
	const std::vector<GLfloat>& getVertexColors() const;
	const std::vector<GLushort>& getIndices() const;
	const std::vector<GLfloat>& getVerticesToSwap() const;
	void swapVertices(const std::pair<size_t, size_t>& indexOfSwap);
	void clearSwaps();

private:
	std::vector<GLfloat> rectangleVertices;
	std::vector<GLfloat> vertexColors;
	std::vector<GLushort> vertexIndices; // the indices used for the element buffer
	std::vector<GLfloat> verticesToSwap;

	const GLfloat normalize(const float& numberToNormalize) const;
};