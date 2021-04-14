#include "Shader.h"

#include <stdio.h>
#include <gl/glew.h>
#include <gl/GL.h>

void Shader::GetShaderCompileInfo(unsigned int id)
{
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = new char[length]();
        glGetShaderInfoLog(id, length, &length, message);

        printf("Failed to compile shader:\n %s\n", message);
        glDeleteShader(id);

        delete []message;
    }
}

unsigned int Shader::CompileShader(const char* fileName, unsigned int type)
{
    FILE *fptr;
    long fileSize;
    char *source;

    fptr = fopen(fileName, "r");

    if(fptr == NULL) { printf("Could not open file %s\n", fileName); }

    fseek(fptr, 0, SEEK_END);
    fileSize = ftell(fptr);
    rewind(fptr);

    source = new char[fileSize]();

    fread(source, fileSize, 1, fptr);
    source[fileSize] = '\0';

    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    GetShaderCompileInfo(id);

    fclose(fptr);
    delete source;

    return id;
}

Shader::Shader(const char *vertexName, const char* fragmentName)
{
        m_ShaderID = glCreateProgram();
        unsigned int vs = CompileShader(vertexName, GL_VERTEX_SHADER);
        unsigned int fs = CompileShader(fragmentName, GL_FRAGMENT_SHADER);

        glAttachShader(m_ShaderID, vs);
        glAttachShader(m_ShaderID, fs);
        glLinkProgram(m_ShaderID);
        glValidateProgram(m_ShaderID);

        glDeleteProgram(vs);
        glDeleteProgram(fs);

        glUseProgram(m_ShaderID);
}