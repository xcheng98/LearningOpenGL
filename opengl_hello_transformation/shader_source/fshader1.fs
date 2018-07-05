#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1; // Not using default, specify the name
uniform sampler2D texture2; // Not using default, specify the name

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.3);

    /* make the face look at another direction */
    /* FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1-TexCoord.x, TexCoord.y)), 0.3); */
}