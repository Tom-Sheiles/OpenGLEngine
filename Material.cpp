#include <stdio.h>

#include "Material.h"
#include <gl/glew.h>
#include <gl/GL.h>

void Material::GetShaderCompileInfo(unsigned int id)
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

unsigned int Material::CompileShader(char* fileName, unsigned int type)
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

float* HexToFv(const char* color)
{
    float *hex = new float[4];

    hex[0] = (int)(color[0] + color[1]) / 255;
    hex[1] = (int)(color[2] + color[3]) / 255;
    hex[2] = (int)(color[4] + color[5]) / 255;
    hex[3] = (int)(color[6] + color[7]) / 255;

    return hex;
}

/*
// This is a fundamnetally flawed method for materials as it recompiles the same shader for each new material
// The material system should compile each shader only on the first material.
// Each new material should then get a pointer to the compiled shader and store a map of uniforms that get
// Set for each draw call.
*/
Material::Material(unsigned int inbuiltShader)
{
    if((inbuiltShader & STANDARD_SHADER) == STANDARD_SHADER)
    {
        m_Shader = glCreateProgram();
        unsigned int vs = CompileShader("./res/Shaders/StandardVertex.GLSL", GL_VERTEX_SHADER);
        unsigned int fs = CompileShader("./res/Shaders/StandardFragment.GLSL", GL_FRAGMENT_SHADER);

        glAttachShader(m_Shader, vs);
        glAttachShader(m_Shader, fs);
        glLinkProgram(m_Shader);
        glValidateProgram(m_Shader);

        glDeleteProgram(vs);
        glDeleteProgram(fs);

        glUseProgram(m_Shader);
    }
}

void Material::Bind()
{
    glUseProgram(m_Shader);
}

void Material::SetColor(const char* name, const char* color)
{
    float *fColor = HexToFv(color);
    glUniform4f(glGetUniformLocation(m_Shader, name), fColor[0], fColor[1], fColor[2], fColor[3]);
}

void Material::SetColor(const char* name, float c0, float c1, float c2, float c3)
{
    glUniform4f(glGetUniformLocation(m_Shader, name), c0/255, c1/255, c2/255, c3/255);
}