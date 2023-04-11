#include "BarChart.h"

BarChart::BarChart()
{
 //   glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    constexpr size_t topRightVertexIndexOffset = 1, bottomRightVertexIndexOffset = 2, bottomLeftVertexIndexOffset = 3;
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
        rectangleVertices.push_back(glm::vec2(xPosition, height.at(i))); // top left
        rectangleVertices.push_back(glm::vec2(xPosition + rectangleWidth, height.at(i))); // top right
        rectangleVertices.push_back(glm::vec2(xPosition + rectangleWidth, windowBottomCoordinate)); // bottom right
        rectangleVertices.push_back(glm::vec2(xPosition, windowBottomCoordinate)); // bottom left

        // RGB color values for each corner vertex
        // the use of std::round is based on https://stackoverflow.com/questions/1914115/converting-color-value-from-float-0-1-to-byte-0-255
        // OpenGL uses floats in the range of 0.0 - 1.0 for color values, but we can store them as unsigned bytes.
        vertexColors.push_back(glm::u8vec3(std::round(topLeftColorR * byteMultiplier), std::round(topLeftColorG * byteMultiplier), std::round(topLeftColorB * byteMultiplier)));
        vertexColors.push_back(glm::u8vec3(std::round(topRightColorR * byteMultiplier), std::round(topRightColorG * byteMultiplier), std::round(topRightColorB * byteMultiplier)));
        vertexColors.push_back(glm::u8vec3(std::round(bottomRightColorR * byteMultiplier), std::round(bottomRightColorG * byteMultiplier), std::round(bottomRightColorB * byteMultiplier)));
        vertexColors.push_back(glm::u8vec3(std::round(bottomLeftColorR * byteMultiplier), std::round(bottomLeftColorG * byteMultiplier), std::round(bottomLeftColorB * byteMultiplier)));

        // Indices used by the element buffer object
        vertexIndices.push_back(static_cast<GLushort>(vertexIndex));
        vertexIndices.push_back(static_cast<GLushort>(vertexIndex + topRightVertexIndexOffset));
        vertexIndices.push_back(static_cast<GLushort>(vertexIndex + bottomRightVertexIndexOffset));
        vertexIndices.push_back(static_cast<GLushort>(vertexIndex + bottomRightVertexIndexOffset));
        vertexIndices.push_back(static_cast<GLushort>(vertexIndex + bottomLeftVertexIndexOffset));
        vertexIndices.push_back(static_cast<GLushort>(vertexIndex));

        topRightColorR += 0.01f;
        xPosition += rectangleWidth;
        vertexIndex += verticesPerRectangle;
    }
}

const std::vector<glm::vec2>& BarChart::getRectangleVertices() const
{
    return rectangleVertices;
}

const std::vector<glm::u8vec3>& BarChart::getVertexColors() const
{
    return vertexColors;
}

const std::vector<GLushort>& BarChart::getIndices() const
{
    return vertexIndices;
}

// Swaps the vertices of 2 rectangles, given the starting index of each rectangle
void BarChart::swapRectangles(const std::pair<size_t, size_t>& indexOfSwap)
{
    constexpr size_t topRightOffset = 1;

    std::swap(rectangleVertices.at(indexOfSwap.first).y, rectangleVertices.at(indexOfSwap.second).y);
    std::swap(rectangleVertices.at(indexOfSwap.first + topRightOffset).y, rectangleVertices.at(indexOfSwap.second + topRightOffset).y);
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

void BarChart::updateRectangle(const size_t indexOfUpdate, const glm::vec2& newValue)
{
    rectangleVertices.at(indexOfUpdate).y = newValue.y;
    rectangleVertices.at(indexOfUpdate + 1).y = newValue.y;
}