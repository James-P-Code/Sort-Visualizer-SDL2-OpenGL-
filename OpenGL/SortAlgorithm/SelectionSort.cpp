#include "SelectionSort.h"

SelectionSort::SelectionSort(BarChart& barChart) : SortAlgorithm(barChart),
												   indexOfMinimum(0) {}

void SelectionSort::sort()
{
	if (sortIterator < numberOfRectangles - 1)
	{
		if (currentVertex < (sortIterator + 1) * verticesPerRectangle)
		{
			// we always use the top left corner y coordinate in our comparisons, which is index 1 on the first iteration of the loop
			indexOfMinimum = (sortIterator * verticesPerRectangle); // first iteration this would be (0 * 8) + 1 = 1, or the index of the first rectangle's top left corner y coordinate
			currentVertex = (sortIterator + 1) * verticesPerRectangle; // first iteration this would be (0 + 1) * 8) + 1 = 9, or the index of the 2nd rectangle's top left corner y coordinate
		}

		if (currentVertex < numberOfRectangles * verticesPerRectangle)
		{
			if (barChart.getVertexPositions().at(currentVertex).y < barChart.getVertexPositions().at(indexOfMinimum).y)
			{
				indexOfMinimum = currentVertex;
			}
			currentVertex += verticesPerRectangle;
		}
		else
		{
			if (indexOfMinimum != 0)
			{
				swapIndices.first = indexOfMinimum;
				swapIndices.second = sortIterator * verticesPerRectangle;
				barChart.swapRectangles(swapIndices);
			}
			currentVertex = 0;
			++sortIterator;
		}
		barChart.setRectangleToHighlight(currentVertex);
	}

	if (indexOfMinimum > 0 && sortIterator == numberOfRectangles - 1)
	{
	//	sortedStatus = true;
	}
}