#version 330 core

layout(location = 0) in vec4 positions;
layout(location = 1) in vec3 color;

out vec3 v_Color;

uniform mat4 u_MVP;

void main()
{
    gl_Position = positions;
    v_Color = color;
}