#pragma once

#include "Shader.h"
#include <iostream>

class Material
{
private:
    Shader *m_Shader;
    std::pair<int, float*> u_Color; //Should be map later for more and non staticlly defined uniforms

public:
    Material();
    ~Material();
    void SetColor(const char* name, float c0, float c1, float c2, float c3);
    void Bind();

    inline Shader *GetShader() {return m_Shader;}
};