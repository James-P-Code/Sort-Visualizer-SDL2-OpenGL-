#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

class BarChart final
{
public:
	BarChart();
	const std::vector<GLfloat>& getRectangleVertices() const;
	const std::vector<GLfloat>& getVertexColors() const;
	const std::vector<GLushort>& getIndices() const; // get the indices used for rendering
	const std::vector<GLfloat>& getSwap() const;
	void sort();
	void clearSwaps();
	const int getCurrent() const;

private:
	std::vector<GLfloat> rectangleVertices;
	std::vector<GLfloat> vertexColors;
	std::vector<GLushort> vertexIndices;
	std::vector<GLfloat> swapVector;
	bool swapOccurred;
	size_t sortIterator = 0, currentVertex = 1;

	const GLfloat normalize(const float& numberToNormalize) const;
	void fillSwapVector(const size_t startingIndex);
};