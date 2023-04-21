#version 460 core
layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec3 vertexColor;

layout (std140, binding = 0) uniform projectionMatrix
{
    mat4 projection;
};

const int maxVertexOffset = 4;

uniform int highlightVertexID;
uniform mat4 model;

out vec3 fragmentColor;

void main()
{
    float zValue = 0.0f;

    if (highlightVertexID <= gl_VertexID && highlightVertexID + maxVertexOffset > gl_VertexID)
    {
       fragmentColor = vec3(0.08, 0.96, 0.19);
       zValue = 0.2f;
    }
    else
    {
        fragmentColor = vertexColor;
    }

    gl_Position = projection * model * vec4(vertexPosition, zValue, 1.0);
}