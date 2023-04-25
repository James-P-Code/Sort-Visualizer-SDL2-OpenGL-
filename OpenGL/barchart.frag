#version 460 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 Highlight;

in vec3 fragmentColor;

void main()
{
	FragColor = vec4(fragmentColor, 0.0);

	if (fragmentColor.rgb == vec3(0.08, 0.96, 0.19))
	{
		Highlight = vec4(fragmentColor, 0.0);
	}
	else
	{
		Highlight = vec4(0.0, 0.0, 0.0, 1.0);
	}
}
/*
out vec4 currentColor;
in vec3 fragmentColor;

void main()
{
	currentColor = vec4(fragmentColor, 0.0);
}
*/