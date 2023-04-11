#include "BubbleSort.h"

BubbleSort::BubbleSort(BarChart& barChart) :  SortAlgorithm(barChart),
                                              swapOccurred(false) {}

void BubbleSort::sort()
{
    swapOccurred = false;

    if (sortIterator < numberOfRectangles)
    {
        if (currentVertex < (numberOfRectangles * verticesPerRectangle) - (sortIterator * verticesPerRectangle) - verticesPerRectangle)
        {
            if (barChart.getRectangleVertices().at(currentVertex).y > barChart.getRectangleVertices().at(currentVertex + verticesPerRectangle).y)
            {
                swapOccurred = true;
                swapIndices.first = currentVertex;
                swapIndices.second = currentVertex + verticesPerRectangle;
                barChart.swapRectangles(swapIndices);
            }
            currentVertex += verticesPerRectangle;
        }
        else
        {
            currentVertex = 0;
            sortIterator++;
            swapOccurred = false;
        }
        barChart.setRectangleToHighlight(currentVertex);
    }

    rectangleToHighlight = currentVertex;

    if (sortIterator == numberOfRectangles)
    {
        //     sortedStatus = true;
    }
}