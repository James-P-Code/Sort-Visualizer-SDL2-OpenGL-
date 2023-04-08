#include "SortAlgorithm.h"

SortAlgorithm::SortAlgorithm(BarChart& barChart) : barChart (barChart), 
										           rectangleVertices (barChart.getRectangleVertices()),
												   swapIndices (std::make_pair(0, 0)),
												   rectangleToHighlight (0) {}

// Sets the index of the rectangle to highlight during the sort.  This index is used by the shader to determine which
// vertices to color to highlight the rectangle that we wish to highlight.  Because we are using vertex indices to render
// each rectangle we have to convert the vertex index to match the render index.  That is what this function does.
void SortAlgorithm::setRectangleToHighlight(const GLint vertexIndexToHighlight)
{
	rectangleToHighlight = ((vertexIndexToHighlight - 1) * 0.5) + 4;
}

const GLint SortAlgorithm::getRectangleToHighlight() const
{
	return rectangleToHighlight;
}

const std::pair<size_t, size_t>& SortAlgorithm::getSwapIndices() const
{
	return swapIndices;
}