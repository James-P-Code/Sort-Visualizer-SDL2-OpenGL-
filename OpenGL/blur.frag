#version 460 core
out vec4 FragColor;
  
in vec2 TexCoords;

layout (binding = 0) uniform sampler2D image;
  
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{             
    vec2 tex_offset = 1.0 / textureSize(image, 0); // gets size of single texel
    vec3 result = texture(image, TexCoords).rgb * weight[0]; // current fragment's contribution
    int passNumber = 0;
    for (int passNumber = 0; passNumber < 10; passNumber++)
    {
        if (passNumber % 2 == 0)
        {
            for(int i = 1; i < 5; ++i)
            {
                result += texture(image, TexCoords + vec2(tex_offset.x * i * 1.75, 0.0)).rgb * weight[i];
                result += texture(image, TexCoords - vec2(tex_offset.x * i * 1.75, 0.0)).rgb * weight[i];
            }
        }
        else
        {
        for(int i = 1; i < 2; ++i)
        {
            result += texture(image, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
        }
    }
   // passNumber++;

    FragColor = vec4(result, 1.0);
}