#version 460 core
layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec3 vertexColor;

const int maxVertexOffset = 4;

uniform int highlightVertexID;
uniform mat4 model;
uniform mat4 projection;

out vec3 fragmentColor;

void main()
{
    gl_Position = projection * model * vec4(vertexPosition.xy, 0.0, 1.0);

    if (highlightVertexID <= gl_VertexID && highlightVertexID + maxVertexOffset > gl_VertexID)
    {
       fragmentColor = vec3(0.08, 0.96, 0.19);
    }
    else
    {
        fragmentColor = vertexColor;
    }
}