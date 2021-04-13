#pragma once

#define STANDARD_SHADER 0x01

class Material
{
private:
    unsigned int m_Shader;

    void GetShaderCompileInfo(unsigned int id);
    unsigned int CompileShader(char* fileName, unsigned int type);

public:
    Material(unsigned int inbuiltShader);
    void SetColor(const char* name, const char* color);
    void SetColor(const char* name, float c0, float c1, float c2, float c3);

    void Bind();

    inline unsigned int GetShader() const { return m_Shader; }
};