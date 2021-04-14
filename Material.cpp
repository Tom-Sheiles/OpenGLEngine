#include <stdio.h>

#include "Material.h"
#include "Renderer.h"
#include <gl/glew.h>
#include <gl/GL.h>


Material::Material(/* Material should eventually take shader option*/)
{
    m_Shader = Renderer::GetStandardShader();
}


void Material::Bind()
{
    glUniform4f(glGetUniformLocation(m_Shader->GetShaderID(), "u_Color"), u_Color.second[0], u_Color.second[1], u_Color.second[2], u_Color.second[3]);
}

void Material::SetColor(const char* name, float c0, float c1, float c2, float c3)
{
    float *color = new float[4]{c0/255, c1/255, c2/255, c3/255};
    u_Color = std::make_pair(glGetUniformLocation(m_Shader->GetShaderID(), name), color);
    delete color;
}