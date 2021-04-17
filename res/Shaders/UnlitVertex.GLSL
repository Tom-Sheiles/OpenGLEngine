#version 330 core

layout(location = 0) in vec4 positions;

int main()
{
    gl_Position = positions;
}