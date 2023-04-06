#include "BubbleSort.h"

BubbleSort::BubbleSort(BarChart& barChart) :  SortAlgorithm(barChart) {}

void BubbleSort::sort()
{
    constexpr int numberOfRectangles = 100;
    constexpr size_t floatsPerRectangle = 8, topLeftOffset = 1;
    swapOccurred = false;

    if (sortIterator < numberOfRectangles)
    {
        if (currentVertex < (numberOfRectangles * floatsPerRectangle) - (sortIterator * floatsPerRectangle) - floatsPerRectangle)
        {
            if (rectangleVertices.at(currentVertex) > rectangleVertices.at(currentVertex + floatsPerRectangle))
            {
                swapOccurred = true;
          //      barChart.swapVertices(currentVertex - topLeftOffset);
                barChart.swapVerticesTest(currentVertex - topLeftOffset, currentVertex + 7);
            }
            firstSwapIndex = currentVertex - 1, secondSwapIndex = currentVertex + 7;
            currentVertex += floatsPerRectangle;
        }
        else
        {
            currentVertex = 1;
            sortIterator++;
            swapOccurred = false;
        }
    }
    
  //  barChart.setSwapIndex(currentVertex);
    rectangleToHighlight = std::floor((currentVertex - 1) / 2);
    if (sortIterator == numberOfRectangles)
    {
        //     sortedStatus = true;
    }
}