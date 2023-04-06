#include "SortAlgorithm.h"

SortAlgorithm::SortAlgorithm(BarChart& barChart) : barChart (barChart), 
										           rectangleVertices (barChart.getRectangleVertices()),
												   swapIndices (std::make_pair(0, 0)),
												   rectangleToHighlight (0) {}

const GLint SortAlgorithm::getRectangleToHighlight() const
{
	return rectangleToHighlight;
}

const std::pair<size_t, size_t>& SortAlgorithm::getSwapIndices() const
{
	return swapIndices;
}