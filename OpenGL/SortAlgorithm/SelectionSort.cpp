#include "SelectionSort.h"

SelectionSort::SelectionSort(BarChart& barChart) : SortAlgorithm(barChart) {}

void SelectionSort::sort()
{
	if (sortIterator < numberOfRectangles - 1)
	{
		if (currentRectangle < (sortIterator + 1) * floatsPerRectangles)
		{
			// we always use the top left corner y coordinate in our comparisons, which is index 1 on the first iteration of the loop
			indexOfMinimum = (sortIterator * floatsPerRectangles) + 1; // first iteration this would be (0 * 8) + 1 = 1, or the index of the first rectangle's top left corner y coordinate
			currentRectangle = ((sortIterator + 1) * floatsPerRectangles) + 1; // first iteration this would be (0 + 1) * 8) + 1 = 9, or the index of the 2nd rectangle's top left corner y coordinate
		}

		if (currentRectangle < numberOfRectangles * floatsPerRectangles)
		{
			if (rectangleVertices.at(currentRectangle) < rectangleVertices.at(indexOfMinimum))
			{
				indexOfMinimum = currentRectangle;
			}
			currentRectangle += floatsPerRectangles;
		}
		else
		{
			if (indexOfMinimum != 1)
			{
				swapIndices.first = indexOfMinimum - 1;
				swapIndices.second = sortIterator * floatsPerRectangles;
				barChart.swapVertices(swapIndices);
			}
			currentRectangle = 1;
			++sortIterator;
		}
		rectangleToHighlight = std::floor((currentRectangle - 1) / 2);
	}

	if (indexOfMinimum > 0 && sortIterator == numberOfRectangles - 1)
	{
	//	sortedStatus = true;
	}
}