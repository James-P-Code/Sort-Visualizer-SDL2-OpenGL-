#include "SortAlgorithm.h"

SortAlgorithm::SortAlgorithm(BarChart& barChart) : barChart(barChart), rectangleVertices(barChart.getRectangleVertices()) {}

size_t SortAlgorithm::getSwapIndex()
{
	return swapIndex;
}

const GLint SortAlgorithm::getRectangleToHighlight() const
{
	return rectangleToHighlight;
}

const size_t SortAlgorithm::getFirstSwapIndex() const
{
	return firstSwapIndex;
}

const size_t SortAlgorithm::getSecondSwapIndex() const
{
	return secondSwapIndex;
}