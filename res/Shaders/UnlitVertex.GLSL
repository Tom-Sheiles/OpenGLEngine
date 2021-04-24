#version 330 core

in vec3 positions;
in vec3 tint;

out vec3 v_Tint;

//uniform mat4 u_ViewProjection;

void main()
{
    //u_ViewProjection = mat4(1.0);   /*    THIS MUST BE SET!!!!!!!!!!!! SET THIS VALUE !!!!!!!!!!!!!!!! FUCK YOU SET THIS VALUE !!!!!!!!!!!   */
    gl_Position = vec4(positions, 1.0);
    v_Tint = tint;
}