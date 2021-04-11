#version 330 core

layout(location = 0) in vec4 positions;

uniform vec4 u_Offset;

void main()
{
    gl_Position = positions + u_Offset;
}