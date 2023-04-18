#include "BarChart.h"

BarChart::BarChart() :rectangleToHighlight(0)
{
    constexpr size_t topRightVertexIndexOffset = 1, bottomRightVertexIndexOffset = 2, bottomLeftVertexIndexOffset = 3;
 //   constexpr GLfloat rectangleWidth = 2.0f / numberOfRectangles; // OpenGL render coordinates are -1 to 1, so this will give the appropriate width for the rectangles
    constexpr int rectangleWidth = windowWidth / numberOfRectangles;
  //  constexpr GLfloat windowBottomCoordinate = -1.0f; // same as the rectangle width, the render coordinates are -1 to 1, where -1 is the bottom of the render area
    constexpr GLfloat windowBottomCoordinate = 800.0f;
    constexpr float byteMultiplier = 255.0f;
    constexpr int bufferSize = 3;
    GLfloat xPosition = 0.0f;
  //  GLfloat xPosition = -1.0f;
    GLfloat topLeftColorR = 0.31f, topLeftColorG = 0.55f, topLeftColorB = 0.91f;
    GLfloat topRightColorR = 0.00f, topRightColorG = 0.37f, topRightColorB = 0.96f;
    GLfloat bottomRightColorR = 0.09f, bottomRightColorG = 0.22f, bottomRightColorB = 0.44f;
    GLfloat bottomLeftColorR = 0.01f, bottomLeftColorG = 0.16f, bottomLeftColorB = 0.42f;
    int vertexIndex = 0;
    std::vector<glm::vec2> screenSpaceFrameBufferVertices;
    std::vector<GLubyte> screenSpaceVertexIndices;
    std::vector<glm::vec2> screenSpaceTextureCoordinates;
    std::array<GLfloat, numberOfRectangles> height;
    std::mt19937 randomSeed(std::random_device{}());

    /*  We will be sorting the rectangles of the bar chart according to their height.  We want the order of the bars to
    *   be random at first (heights in random order).  To facilitate this we will first fill an array with a normalized
    *   height value for each rectangle.  Then we will shuffle that array so the heights are in a random order.  We will
    *   then create the rectangles using this random ordering of height values.  */
    for (int i = 0; i < numberOfRectangles; ++i)
    {
          height.at(i) = normalize(static_cast<float>(i));
     //   height.at(i) = static_cast<float>(i);
    }

    std::shuffle(std::begin(height), std::end(height), randomSeed);
  
    for (size_t i = 0; i < numberOfRectangles; ++i)
    {
        vertexPositions.push_back(glm::vec2(xPosition, height.at(i))); // top left
        vertexPositions.push_back(glm::vec2(xPosition + rectangleWidth, height.at(i))); // top right
        vertexPositions.push_back(glm::vec2(xPosition + rectangleWidth, windowBottomCoordinate)); // bottom right
        vertexPositions.push_back(glm::vec2(xPosition, windowBottomCoordinate)); // bottom left

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

    // RGB color values for each corner vertex
    // the use of std::round is based on https://stackoverflow.com/questions/1914115/converting-color-value-from-float-0-1-to-byte-0-255
    // OpenGL uses floats in the range of 0.0 - 1.0 for color values, but we can store them as unsigned bytes.
    // Because we will use a triple buffer we need 3 sets of the same colors
    for (int i = 0; i < bufferSize; ++i)
    {
        for (int j = 0; j < numberOfRectangles; ++j)
        {
            vertexColors.push_back(glm::u8vec3(std::round(topLeftColorR * byteMultiplier), std::round(topLeftColorG * byteMultiplier), std::round(topLeftColorB * byteMultiplier)));
            vertexColors.push_back(glm::u8vec3(std::round(topRightColorR * byteMultiplier), std::round(topRightColorG * byteMultiplier), std::round(topRightColorB * byteMultiplier)));
            vertexColors.push_back(glm::u8vec3(std::round(bottomRightColorR * byteMultiplier), std::round(bottomRightColorG * byteMultiplier), std::round(bottomRightColorB * byteMultiplier)));
            vertexColors.push_back(glm::u8vec3(std::round(bottomLeftColorR * byteMultiplier), std::round(bottomLeftColorG * byteMultiplier), std::round(bottomLeftColorB * byteMultiplier)));

            topRightColorR += 0.01f;
        }
        topRightColorR = 0.00f;
    }

    barChartShader.loadFromFile("barchart.vert", "barchart.frag");
    shaderHighlightUniformLocation = glGetUniformLocation(barChartShader.getProgramID(), "highlightVertexID");
    barChartVertexBuffer.createPersistentMappedBuffer(vertexPositions, vertexColors, vertexIndices);

    barChartProjectionLoc = glGetUniformLocation(barChartShader.getProgramID(), "projection");
    barChartModelLoc = glGetUniformLocation(barChartShader.getProgramID(), "model");

    highlightShader.loadFromFile("highlight.vert", "highlight.frag");

    screenSpaceFrameBufferVertices.push_back(glm::vec2(-1.0f, 1.0f));
    screenSpaceFrameBufferVertices.push_back(glm::vec2(1.0f, 1.0f));
    screenSpaceFrameBufferVertices.push_back(glm::vec2(1.0f, -1.0f));
    screenSpaceFrameBufferVertices.push_back(glm::vec2(-1.0f, -1.0f));

    screenSpaceVertexIndices.push_back(0);
    screenSpaceVertexIndices.push_back(1);
    screenSpaceVertexIndices.push_back(2);
    screenSpaceVertexIndices.push_back(2);
    screenSpaceVertexIndices.push_back(3);
    screenSpaceVertexIndices.push_back(0);

    screenSpaceTextureCoordinates.push_back(glm::vec2(0.0f, 1.0f));
    screenSpaceTextureCoordinates.push_back(glm::vec2(1.0f, 1.0f));
    screenSpaceTextureCoordinates.push_back(glm::vec2(1.0f, 0.0f));
    screenSpaceTextureCoordinates.push_back(glm::vec2(0.0f, 0.0f));

    screenSpaceVertexBuffer.createScreenSpaceBuffer(screenSpaceFrameBufferVertices, screenSpaceTextureCoordinates, screenSpaceVertexIndices);
    screenSpaceShader.loadFromFile("screenspace.vert", "screenspace.frag");

    frameBuffer.createFrameBuffer();
}

void BarChart::draw()
{

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 highlightRectangleMatrix = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
 //   highlightRectangleMatrix = glm::translate(highlightRectangleMatrix, glm::vec3((rectangleToHighlight / 4) * 6.0f, 800.0f, 0.0f));

  //  int projectionShaderLoc = glGetUniformLocation(highlightShader.getProgramID(), "projection");
  //  int highlightShaderLoc = glGetUniformLocation(highlightShader.getProgramID(), "highlightRectangleMatrix");
    float scaleFactor = 1.3f;

 //   glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer.getFrameBuffer());
 //   glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  //  glStencilMask(0x00);

    barChartVertexBuffer.update(vertexPositions);
    barChartShader.useProgram();
    glUniformMatrix4fv(barChartModelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(barChartProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glBindVertexArray(barChartVertexBuffer.getVertexArray());
    glDrawElementsBaseVertex(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_SHORT, nullptr, barChartVertexBuffer.getBufferDataStartIndex());
    glBindVertexArray(0);
    barChartVertexBuffer.lock();

    /*
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);

  //  glBindVertexArray(barChartVertexBuffer.getVertexArray());
    glUniform1i(shaderHighlightUniformLocation, rectangleToHighlight + barChartVertexBuffer.getBufferDataStartIndex());
    glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr, rectangleToHighlight + barChartVertexBuffer.getBufferDataStartIndex());

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    highlightShader.useProgram();

    highlightRectangleMatrix = glm::translate(highlightRectangleMatrix, glm::vec3(6 * 0.5f, 1.0f, 0.0f));
    highlightRectangleMatrix = glm::scale(highlightRectangleMatrix, glm::vec3(60000000, 400, 60000));
    glUniformMatrix4fv(projectionShaderLoc, 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(highlightShaderLoc, 1, GL_FALSE, &highlightRectangleMatrix[0][0]);
    glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr, rectangleToHighlight + barChartVertexBuffer.getBufferDataStartIndex());

    glBindVertexArray(0);
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glEnable(GL_DEPTH_TEST);
    */

 //   SDL_Delay(100);
  //  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  //  glDisable(GL_DEPTH_TEST);
    // clear all relevant buffers
  //  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
 //   glClear(GL_COLOR_BUFFER_BIT);

   // screenSpaceShader.useProgram();
  //  glBindVertexArray(screenSpaceVertexBuffer.getVertexArray());
  //  glBindTextureUnit(0, frameBuffer.getFrameBufferTexture());
  //  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
}

const std::vector<glm::vec2>& BarChart::getVertexPositions() const
{
    return vertexPositions;
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

    std::swap(vertexPositions.at(indexOfSwap.first).y, vertexPositions.at(indexOfSwap.second).y);
    std::swap(vertexPositions.at(indexOfSwap.first + topRightOffset).y, vertexPositions.at(indexOfSwap.second + topRightOffset).y);
}

// normalize a number to be within the range of the OpenGL render coordinates (-1 to 1)
const GLfloat BarChart::normalize(const float& numberToNormalize) const
{
    constexpr float minRange = 0.f;
    constexpr float maxRange = static_cast<float>(numberOfRectangles);
    constexpr float minBarHeight = 10.0f;
 //   constexpr float minBarHeight = -0.97f;
 //   constexpr float maxBarHeight = 1.0f;
    constexpr float maxBarHeight = 600.0f;

    return (numberToNormalize - minRange) / (maxRange - minRange) * (maxBarHeight - minBarHeight) + minBarHeight;
}

void BarChart::updateRectangle(const size_t indexOfUpdate, const glm::vec2& newValue)
{
    vertexPositions.at(indexOfUpdate).y = newValue.y;
    vertexPositions.at(indexOfUpdate + 1).y = newValue.y;
}

void BarChart::setRectangleToHighlight(const int rectangleToHighlight)
{
    this->rectangleToHighlight = rectangleToHighlight;
}