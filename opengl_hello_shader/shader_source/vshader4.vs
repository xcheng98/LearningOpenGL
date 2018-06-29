/* Add horizontal offset */
#version 330 core
layout (location = 0) in vec3 aPos;
uniform vec2 ourOffset;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    gl_Position = gl_Position + vec4(ourOffset, 0.0, 1.0);
}