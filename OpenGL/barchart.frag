#version 460 core
layout (location = 0) out lowp vec4 fullScene; // output to color buffer of the full scene
layout (location = 1) out lowp vec4 highlightOnly; // output to color buffer of just the highlighted rectangle

in vec3 fragmentColor;

void main()
{
	fullScene = vec4(fragmentColor, 0.0);

	fragmentColor.rgb == vec3(0.08, 0.96, 0.19) ? highlightOnly = vec4(fragmentColor, 1.0) : highlightOnly = vec4(0.0);
}