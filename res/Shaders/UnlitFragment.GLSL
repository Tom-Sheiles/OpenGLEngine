#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Tint;

void main()
{
    color = vec4(v_Tint, 1.0);
}