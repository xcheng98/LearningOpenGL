#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1; // Not using default, specify the name
uniform sampler2D texture2; // Not using default, specify the name
uniform float adjustment;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), adjustment);
}