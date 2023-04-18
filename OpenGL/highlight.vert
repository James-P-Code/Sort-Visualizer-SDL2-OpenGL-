#version 460 core
layout (location = 0) in vec2 aPos;

uniform mat4 projection;
uniform mat4 highlightRectangleMatrix;

void main()
{ 
    gl_Position = projection * highlightRectangleMatrix * vec4(aPos.xy, 0.0, 1.0f);
}