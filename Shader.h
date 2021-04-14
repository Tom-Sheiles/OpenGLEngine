#pragma once

class Shader
{
private:
    void GetShaderCompileInfo(unsigned int id);
    unsigned int CompileShader(const char* fileName, unsigned int type);

    unsigned int m_ShaderID;

public:
    Shader(const char *vertexName, const char* fragmentName);
    inline unsigned int GetShaderID() { return m_ShaderID; }
};


