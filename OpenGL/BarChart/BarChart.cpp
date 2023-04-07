#include "BarChart.h"

BarChart::BarChart()
{
    constexpr size_t topRightVertexIndexOffset = 1, bottomRightVertexIndexOffset = 2, bottomLeftVertexIndexOffset = 3;
    constexpr int numberOfRectangles = 100, verticesPerRectangle = 4;
    constexpr GLfloat rectangleWidth = 2.0f / numberOfRectangles; // OpenGL render coordinates are -1 to 1, so this will give the appropriate width for the rectangles
    constexpr GLfloat windowBottomCoordinate = -1.0f; // same as the rectangle width, the render coordinates are -1 to 1, where -1 is the bottom of the render area
    constexpr float byteMultiplier = 255.0f;
    GLfloat xPosition = -1.0f;
    GLfloat topLeftColorR = 0.31f, topLeftColorG = 0.55f, topLeftColorB = 0.91f;
    GLfloat topRightColorR = 0.00f, topRightColorG = 0.37f, topRightColorB = 0.96f;
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

        // RGB color values for each corner vertex
        // the use of std::round is based on https://stackoverflow.com/questions/1914115/converting-color-value-from-float-0-1-to-byte-0-255
        // OpenGL uses floats in the range of 0.0 - 1.0 for color values, but we can store them as unsigned bytes.
        vertexColors.push_back(std::round(topLeftColorR * byteMultiplier));
        vertexColors.push_back(std::round(topLeftColorG * byteMultiplier));
        vertexColors.push_back(std::round(topLeftColorB * byteMultiplier));

        vertexColors.push_back(std::round(topRightColorR * byteMultiplier));
        vertexColors.push_back(std::round(topRightColorG * byteMultiplier));
        vertexColors.push_back(std::round(topRightColorB * byteMultiplier));

        vertexColors.push_back(std::round(bottomRightColorR * byteMultiplier));
        vertexColors.push_back(std::round(bottomRightColorG * byteMultiplier));
        vertexColors.push_back(std::round(bottomRightColorB * byteMultiplier));

        vertexColors.push_back(std::round(bottomLeftColorR * byteMultiplier));
        vertexColors.push_back(std::round(bottomLeftColorG * byteMultiplier));
        vertexColors.push_back(std::round(bottomLeftColorB * byteMultiplier));

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

const std::vector<GLubyte>& BarChart::getVertexColors() const
{
    return vertexColors;
}

const std::vector<GLushort>& BarChart::getIndices() const
{
    return vertexIndices;
}

const std::vector<GLfloat>& BarChart::getVerticesToSwap() const
{
    return verticesToSwap;
}

// Swaps the vertices of 2 rectangles, given the starting index of each rectangle.  The index parameters should be equal to the index of the top left corner X vertex 
// for each rectangle.  This function will swap the vertices and prepare a vector consisting of the swapped vertices.  That vector will be used to update the vertex
// buffer object that is used for rendering.
void BarChart::swapVertices(const std::pair<size_t, size_t>& indexOfSwap)
{
    constexpr int floatsPerRectange = 8;
    constexpr size_t topLeftYOffset = 1, topRightYOffset = 3;
    constexpr size_t currentRectangleTopLeftYIndex = 1, currentRectangleTopRightYIndex = 3;
    constexpr size_t nextRectangleTopLeftYIndex = 9, nextRectangleTopRightYIndex = 11;
    verticesToSwap.resize(floatsPerRectange * 2);

    // we aren't swapping any x coordinates so we can fill the swap vector with the all the data of the current and next rectangle before we swap the y coordinates
    for (size_t i = 0; i < floatsPerRectange; ++i)
    {
        verticesToSwap.at(i) = rectangleVertices.at(i + indexOfSwap.first);
        verticesToSwap.at(i + floatsPerRectange) = rectangleVertices.at(i + indexOfSwap.second);
    }

    // because the top left and top right corners share the same y value we only need 1 temporary height value for the swap
    GLfloat tempYPosition = rectangleVertices.at(indexOfSwap.first + topLeftYOffset);

    verticesToSwap.at(currentRectangleTopLeftYIndex) = rectangleVertices.at(indexOfSwap.second + topLeftYOffset);
    verticesToSwap.at(currentRectangleTopRightYIndex) = rectangleVertices.at(indexOfSwap.second + topRightYOffset);
    verticesToSwap.at(nextRectangleTopLeftYIndex) = rectangleVertices.at(indexOfSwap.first + topLeftYOffset);
    verticesToSwap.at(nextRectangleTopRightYIndex) = rectangleVertices.at(indexOfSwap.first + topRightYOffset);

    rectangleVertices.at(indexOfSwap.first + topLeftYOffset) = rectangleVertices.at(indexOfSwap.second + topLeftYOffset);
    rectangleVertices.at(indexOfSwap.first + topRightYOffset) = rectangleVertices.at(indexOfSwap.second + topRightYOffset);
    rectangleVertices.at(indexOfSwap.second + topLeftYOffset) = tempYPosition;
    rectangleVertices.at(indexOfSwap.second + topRightYOffset) = tempYPosition;
}

void BarChart::clearSwaps()
{
    verticesToSwap.clear();
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