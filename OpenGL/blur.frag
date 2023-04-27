#version 460 core
layout (location = 1) out lowp vec4 highlightOnly;
  
in vec2 textureCoordinates;

layout (binding = 0) uniform sampler2D image;
  
const float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{             
    vec2 tex_offset = 1.0 / textureSize(image, 0); // gets size of single texel
    vec3 result = texture(image, textureCoordinates).rgb * weight[0]; // current fragment's contribution

    for(int i = 1; i < 5; ++i)
    {
        result += texture(image, textureCoordinates + vec2(tex_offset.x * i * 1.75, 0.0)).rgb * weight[i]; // * 10 here gives stronger glow but causes artifacts
        result += texture(image, textureCoordinates - vec2(tex_offset.x * i * 1.75, 0.0)).rgb * weight[i] * 10;
    }
        
    for(int i = 1; i < 2; ++i)
    {
        result += texture(image, textureCoordinates + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        result += texture(image, textureCoordinates - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
    } 

    highlightOnly = vec4(result, 1.0);
}