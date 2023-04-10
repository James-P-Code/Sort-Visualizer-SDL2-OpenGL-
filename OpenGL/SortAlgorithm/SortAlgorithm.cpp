#include "SortAlgorithm.h"

SortAlgorithm::SortAlgorithm(BarChart& barChart) : barChart (barChart),
												   swapIndices(std::make_pair(0, 0)),
												   updateSingleRectangleStatus (false),
												   currentVertex (0),
												   sortIterator (0),
												   rectangleToHighlight (0) {}

const size_t SortAlgorithm::getCurrentVertex() const
{
	return currentVertex;
}

const GLint SortAlgorithm::getRectangleToHighlight() const
{
	return rectangleToHighlight;
}

const std::pair<size_t, size_t>& SortAlgorithm::getSwapIndices() const
{
	return swapIndices;
}

const bool SortAlgorithm::updateSingleRectangle() const
{
	return updateSingleRectangleStatus;
}