#version 410 core
out vec4 baseColor;
in vec3 myColor;

void main()
{
	baseColor = vec4(myColor, 1.0);
} 