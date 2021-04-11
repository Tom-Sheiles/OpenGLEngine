#ifndef UNICODE
#define UNICODE
#endif

#include "Engine.h"
#include <gl/glew.h>
#include <gl/GL.h>

#include <Windows.h>
#include <iostream>
#include <stdio.h>

void GetShaderCompileInfo(unsigned int id)
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

unsigned int CompileShader(char* fileName, unsigned int type)
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


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    Engine *engine = new Engine(L"APP", 780, 250, 500, 500, hInstance, CREATE_CONSOLE);

    glClearColor(0.91f, 0.67f, 0.33f, 1.0f);
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;


    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f, 0.5f,
        -0.5f, 0.5f
    };

    unsigned int indicies[]
    {
        0, 1, 2,
        2, 3, 0
    };

    // VERTEX BUFFER
    unsigned int VertexBuffer;
    glGenBuffers(1, &VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    // VBA
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // INDEX BUFFER
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW);


    // SHADER
    unsigned int shader = glCreateProgram();
    unsigned int vs = CompileShader("./Shaders/StandardVertex.GLSL", GL_VERTEX_SHADER);
    unsigned int fs = CompileShader("./Shaders/StandardFragment.GLSL", GL_FRAGMENT_SHADER);

    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);
    glValidateProgram(shader);

    glDeleteProgram(vs);
    glDeleteProgram(fs);

    glUseProgram(shader);
    
    int offset = glGetUniformLocation(shader, "u_Offset");
    int color = glGetUniformLocation(shader, "u_Color");

    float x = 0;
    float y = 0;
    int vecX = 1;
    int vecY = 1;

    // Main Loop
    while(engine->EngineRunning())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // DRAW CALL 1
        glUniform4f(offset, 0.0, 0.0, 0.0, 2.0);
        glUniform4f(color, 0.1, 0.8, 0.6, 1.0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // DRAW CALL 2
        glUniform4f(offset, x, y, 0.0, 2.0);
        glUniform4f(color, 0.94, 0.26, 0.26, 1.0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        x += vecX * 0.1f;
        y += vecY * 0.09f;

        if(x >= 2.5f || x <= -2.5f) vecX = -(vecX);
        if(y >= 2.5f || y <= -2.5f) vecY = -(vecY);

        engine->SwapGLBuffers();
    }

    return 0;
}