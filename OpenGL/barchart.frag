#version 460 core
layout (location = 0) out lowp vec4 fullScene;
layout (location = 1) out lowp vec4 highlightOnly;
// layout (location = 2) out lowp vec4 blur;

in vec3 fragmentColor;

void main()
{
	fullScene = vec4(fragmentColor, 0.0);

	fragmentColor.rgb == vec3(0.08, 0.96, 0.19) ? highlightOnly = vec4(fragmentColor, 0.0) : highlightOnly = vec4(0.0, 0.0, 0.0, 1.0);
}