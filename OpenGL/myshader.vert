#version 460 core
layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec3 vertexColor;

const int maxIndexOffset = 3;
uniform int highlightVertexID;
out vec3 fragmentColor;

void main()
{
    gl_Position = vec4(vertexPosition.x, vertexPosition.y, 0.0, 1.0);

    if (highlightVertexID >= gl_VertexID && highlightVertexID <= gl_VertexID + maxIndexOffset)
    {
        fragmentColor = vec3(0.08, 0.96, 0.19);
    }
    else
    {
        fragmentColor = vertexColor;
    }
}