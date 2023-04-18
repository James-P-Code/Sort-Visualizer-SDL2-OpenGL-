#include "InsertionSort.h"

InsertionSort::InsertionSort(BarChart& barChart) : SortAlgorithm(barChart),
												   keyVertex(glm::vec2(0.0f, 0.0f)),
											       newIteration(true),
												   resetCurrentVertex(false)
{
	sortIterator = verticesPerRectangle;
}

void InsertionSort::sort()
{
	updateSingleRectangleStatus = false;

	if (sortIterator < numberOfRectangles * verticesPerRectangle)
	{
		if (newIteration)
		{
			keyVertex = barChart.getVertexPositions().at(sortIterator);
			currentVertex = sortIterator - verticesPerRectangle;
			newIteration = false;
		}

		if (currentVertex >= 0 && barChart.getVertexPositions().at(currentVertex).y > keyVertex.y)
		{
			swapIndices.first = currentVertex + verticesPerRectangle;
			swapIndices.second = currentVertex;
			barChart.swapRectangles(swapIndices);
			barChart.setRectangleToHighlight(currentVertex);
			currentVertex == 0 ? resetCurrentVertex = true : currentVertex -= verticesPerRectangle;
		}

		if (resetCurrentVertex || barChart.getVertexPositions().at(currentVertex).y < keyVertex.y)
		{
			resetCurrentVertex ? currentVertex = 0 : currentVertex += verticesPerRectangle;
			barChart.updateRectangle(currentVertex, keyVertex);
			updateSingleRectangleStatus = true;
			newIteration = true;
			resetCurrentVertex = false;
			sortIterator += verticesPerRectangle;
		}
	}

	if (sortIterator == numberOfRectangles)
	{
	//	sortedStatus = true;
	}
}