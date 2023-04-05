#include "BarChart.h"

BarChart::BarChart()
{
    constexpr size_t topRightVertexIndexOffset = 1, bottomRightVertexIndexOffset = 2, bottomLeftVertexIndexOffset = 3;
    constexpr int numberOfRectangles = 100, verticesPerRectangle = 4;
    constexpr GLfloat rectangleWidth = 2.0f / numberOfRectangles; // OpenGL render coordinates are -1 to 1, so this will give the appropriate width for the rectangles
    constexpr GLfloat windowBottomCoordinate = -1.0f; // same as the rectangle width, the render coordinates are -1 to 1, where -1 is the bottom of the render area
    GLfloat xPosition = -1.0f;
    GLfloat topLeftColorR = 0.31f, topLeftColorG = 0.55f, topLeftColorB = 0.91f;
    GLfloat topRightColorR = 0.03f, topRightColorG = 0.37f, topRightColorB = 0.96f;
    GLfloat bottomRightColorR = 0.09f, bottomRightColorG = 0.22f, bottomRightColorB = 0.44f;
    GLfloat bottomLeftColorR = 0.01f, bottomLeftColorG = 0.16f, bottomLeftColorB = 0.42f;
    int vertexIndex = 0;
    std::array<GLfloat, numberOfRectangles> height;
    std::mt19937 randomSeed(std::random_device{}());

    /*  We will be sorting the rectangles of the bar chart according to their height.  We want the order of the bars to
    *   be random at first (heights in random order).  To facilitate this we will first fill an array with a normalized
    *   height value for each rectangle.  Then we will shuffle that array so the heights are in a random order.  We will
    *   then create the rectangles using this random ordering of height values.  */
    for (int i = 0; i < numberOfRectangles; ++i)
    {
        height.at(i) = normalize(static_cast<float>(i));
    }

    std::shuffle(std::begin(height), std::end(height), randomSeed);
  
    for (size_t i = 0; i < numberOfRectangles; ++i)
    {
        // top left
        rectangleVertices.push_back(xPosition); // top left x
        rectangleVertices.push_back(height.at(i)); // top left y

        // top right
        rectangleVertices.push_back(xPosition + rectangleWidth); // top right x
        rectangleVertices.push_back(height.at(i)); //top right y

        // bottom right
        rectangleVertices.push_back(xPosition + rectangleWidth); // bottom right x
        rectangleVertices.push_back(windowBottomCoordinate); // bottom right y

        //bottom left
        rectangleVertices.push_back(xPosition); // bottom left x
        rectangleVertices.push_back(windowBottomCoordinate); // bottom left y

        vertexColors.push_back(topLeftColorR);
        vertexColors.push_back(topLeftColorG);
        vertexColors.push_back(topLeftColorB);

        vertexColors.push_back(topRightColorR);
        vertexColors.push_back(topRightColorG);
        vertexColors.push_back(topRightColorB);

        vertexColors.push_back(bottomRightColorR);
        vertexColors.push_back(bottomRightColorG);
        vertexColors.push_back(bottomRightColorB);

        vertexColors.push_back(bottomLeftColorR);
        vertexColors.push_back(bottomLeftColorG);
        vertexColors.push_back(bottomLeftColorB);

        topRightColorR += 0.01f;

        // Indices used by the element buffer object
        vertexIndices.push_back(static_cast<GLushort>(vertexIndex));
        vertexIndices.push_back(static_cast<GLushort>(vertexIndex + topRightVertexIndexOffset));
        vertexIndices.push_back(static_cast<GLushort>(vertexIndex + bottomRightVertexIndexOffset));
        vertexIndices.push_back(static_cast<GLushort>(vertexIndex + bottomRightVertexIndexOffset));
        vertexIndices.push_back(static_cast<GLushort>(vertexIndex + bottomLeftVertexIndexOffset));
        vertexIndices.push_back(static_cast<GLushort>(vertexIndex));

        xPosition += rectangleWidth;
        vertexIndex += verticesPerRectangle;
    }
}

const std::vector<GLfloat>& BarChart::getRectangleVertices() const
{
    return rectangleVertices;
}

const std::vector<GLfloat>& BarChart::getVertexColors() const
{
    return vertexColors;
}

const std::vector<GLushort>& BarChart::getIndices() const
{
    return vertexIndices;
}

// normalize a number to be within the range of the OpenGL render coordinates (-1 to 1)
const GLfloat BarChart::normalize(const float& numberToNormalize) const
{
    constexpr float minRange = 0.f;
    constexpr float maxRange = 100.f;
    constexpr float minBarHeight = -0.97f;
    constexpr float maxBarHeight = 1.0f;

    return (numberToNormalize - minRange) / (maxRange - minRange) * (maxBarHeight - minBarHeight) + minBarHeight;
}

const std::vector<GLfloat>& BarChart::getSwap() const
{
    return swapVector;
}

void BarChart::sort()
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
                fillSwapVector(currentVertex - topLeftOffset);
            }
            currentVertex += floatsPerRectangle;
        }
        else
        {
            currentVertex = 1;
            sortIterator++;
            swapOccurred = false;
        }

     //   setRectanglesToHighlight(currentRectangle, greenHighlightColor);
    }

    if (sortIterator == numberOfRectangles)
    {
   //     sortedStatus = true;
    }
}

void BarChart::fillSwapVector(const size_t startingIndex)
{
    /* This function gets the data needed to update the vertex buffer.  Essentially we are swapping the vertices of 2 rectangles, and
    *  each rectangle has 8 floats that represent the x and y coordinates of each corner.  4 corners * 2 floats per corner = 8.
    *  The first float (which we can think of as index 0, or the startingIndex parameter) is the x coordinate of the top left corner
    *  of the rectangle.  This means that index 1 is the y coordinate of the that same top left corner.  Every corner follows this pattern
    *  of x, y.  Thus the top left y coordinate of the next rectangle (the next rectangle being the one we are swapping with) is at
    *  index 9 (or 1 + 8).  This pattern determines the values that are swapped within this function      */
    constexpr int floatsPerRectange = 8;
    constexpr size_t currentRectangleTopLeftYPosition = 1, currentRectangleTopRightYPosition = 3;
    constexpr size_t nextRectangleTopLeftYPosition = 9, nextRectangleTopRightYPosition = 11;
    swapVector.clear();

    // we aren't swapping any x coordinates so we can fill the swap vector with the all the data of the current and next rectangle before we swap the y coordinates
    for (int i = startingIndex; i < startingIndex + (floatsPerRectange * 2); ++i)
        swapVector.push_back(rectangleVertices.at(i));

    // because the top left and top right corners share the same y value we only need 1 temporary height value for the swap
    GLfloat tempHeight = rectangleVertices.at(startingIndex + currentRectangleTopLeftYPosition);

    swapVector.at(currentRectangleTopLeftYPosition) = rectangleVertices.at(startingIndex + nextRectangleTopLeftYPosition);
    swapVector.at(currentRectangleTopRightYPosition) = rectangleVertices.at(startingIndex + nextRectangleTopLeftYPosition);

    swapVector.at(nextRectangleTopLeftYPosition) = rectangleVertices.at(startingIndex + currentRectangleTopLeftYPosition);
    swapVector.at(nextRectangleTopRightYPosition) = rectangleVertices.at(startingIndex + currentRectangleTopLeftYPosition);

    rectangleVertices.at(startingIndex + currentRectangleTopLeftYPosition) = rectangleVertices.at(startingIndex + nextRectangleTopLeftYPosition);
    rectangleVertices.at(startingIndex + currentRectangleTopRightYPosition) = rectangleVertices.at(startingIndex + nextRectangleTopRightYPosition);

    rectangleVertices.at(startingIndex + nextRectangleTopLeftYPosition) = tempHeight;
    rectangleVertices.at(startingIndex + nextRectangleTopRightYPosition) = tempHeight;
}

void BarChart::clearSwaps()
{
    swapVector.clear();
}

const int BarChart::getCurrent() const
{
    return currentVertex;
}