#version 460 core
out lowp vec4 outputFrag;

in mediump vec2 textureCoordinates;

layout (binding = 0) uniform sampler2D fullScene;
layout (binding = 1) uniform sampler2D activeHighlight;

void main()
{             
	vec3 outputTexture = texture(activeHighlight, textureCoordinates).rgb;
	outputTexture += texture(fullScene, textureCoordinates).rgb;
	outputFrag = vec4(outputTexture, 1.0);
}