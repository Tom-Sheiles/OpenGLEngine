#version 330 core

layout(location = 0) in vec4 positions;
layout(location = 1) in vec3 color;

out vec3 v_Color;

uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = u_ViewProjection * positions;
    v_Color = color;
}