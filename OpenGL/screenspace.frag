#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

layout (binding = 0) uniform sampler2D fullScene;
layout (binding = 1) uniform sampler2D activeHighlight;

void main()
{             
	vec3 textureColor = texture(activeHighlight, TexCoords).rgb;
	textureColor += texture(fullScene, TexCoords).rgb;
	FragColor = vec4(textureColor, 1.0);
}