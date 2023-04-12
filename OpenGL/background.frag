#version 460 core
out vec4 currentColor;

in vec3 fragmentColor;
in vec2 textureCoordinates;

uniform sampler2D backgroundTexture;

void main()
{
	currentColor = texture(backgroundTexture, textureCoordinates);
}