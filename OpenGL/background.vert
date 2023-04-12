#version 460 core
layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 inTextureCoordinates;

out vec3 fragmentColor;
out vec2 textureCoordinates;

void main()
{
	gl_Position = vec4(vertexPosition, 0.0, 1.0);
	fragmentColor = vertexColor;
	textureCoordinates = inTextureCoordinates;
}