#version 330 core

layout(location = 0) in vec4 positions;

uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = positions * u_ViewProjection;
}