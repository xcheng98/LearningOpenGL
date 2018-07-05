#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1; // Not using default, specify the name
uniform sampler2D texture2; // Not using default, specify the name

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.3);

}