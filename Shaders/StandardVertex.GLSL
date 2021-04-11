#version 330 core

layout(location = 0) in vec4 positions;

void main()
{
    vec4 offset = vec4(0.45, 0.45, 0.0, 0.0);
    gl_Position = positions - offset;
}