#include "BubbleSort.h"

BubbleSort::BubbleSort(BarChart& barChart) :  SortAlgorithm(barChart) {}

void BubbleSort::sort()
{
    constexpr int numberOfRectangles = 100;
    constexpr size_t floatsPerRectangle = 8, currentRectangleTopLeftOffset = 1, nextRectangleTopLeftOffset = 7;
    swapOccurred = false;

    if (sortIterator < numberOfRectangles)
    {
        if (currentVertex < (numberOfRectangles * floatsPerRectangle) - (sortIterator * floatsPerRectangle) - floatsPerRectangle)
        {
            if (rectangleVertices.at(currentVertex) > rectangleVertices.at(currentVertex + floatsPerRectangle))
            {
                swapOccurred = true;
                swapIndices.first = currentVertex - currentRectangleTopLeftOffset;
                swapIndices.second = currentVertex + nextRectangleTopLeftOffset;
                barChart.swapVertices(swapIndices);
            }
            currentVertex += floatsPerRectangle;
        }
        else
        {
            currentVertex = 1;
            sortIterator++;
            swapOccurred = false;
        }
    }

    rectangleToHighlight = std::floor((currentVertex - 1) / 2);
    if (sortIterator == numberOfRectangles)
    {
        //     sortedStatus = true;
    }
}