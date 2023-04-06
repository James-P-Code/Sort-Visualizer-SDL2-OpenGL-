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
	void setSwapIndex(const size_t swapIndex);
	const size_t getSwapIndex() const;
	void clearSwaps();
	void swapVertices(const size_t startingIndex);
	void swapVerticesTest(const size_t, const size_t);

private:
	std::vector<GLfloat> rectangleVertices;
	std::vector<GLfloat> vertexColors;
	std::vector<GLushort> vertexIndices; // the indices used for the element buffer
	std::vector<GLfloat> verticesToSwap;
	size_t sortIterator = 0, currentVertex = 1, swapIndex;

	const GLfloat normalize(const float& numberToNormalize) const;
};