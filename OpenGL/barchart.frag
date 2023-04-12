#version 460 core
out vec4 currentColor;
in vec3 fragmentColor;

void main()
{
	currentColor = vec4(fragmentColor, 0.0);
} 