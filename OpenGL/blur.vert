#version 460 core
layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec2 aTextureCoordinate;

out mediump vec2 textureCoordinates;

void main()
{
    gl_Position = vec4(vertexPosition, 0.0, 1.0); 
    textureCoordinates = aTextureCoordinate;
}  