#version 410 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 vColor;

const int maxIndexOffset = 4;
uniform int highlightVertex;
out vec3 myColor;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);

    if (highlightVertex == gl_VertexID || (highlightVertex > gl_VertexID && highlightVertex <= gl_VertexID + maxIndexOffset))
    {
        myColor = vec3(0.08, 0.96, 0.19);
    }
    else
    {
        myColor = vColor;
    }
}