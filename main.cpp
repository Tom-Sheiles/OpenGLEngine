#ifndef UNICODE
#define UNICODE
#endif

#include "Engine.h"
#include <gl/glew.h>
#include <gl/GL.h>

#include <Windows.h>
#include <iostream>
#include <stdio.h>

#include "Math.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
    float screenWidth = 1280;
    float screenHeight = 720;

    Engine *engine = new Engine(L"APP", 320, 150, screenWidth, screenHeight, hInstance, CREATE_CONSOLE);

    glClearColor(0.91f, 0.67f, 0.33f, 1.0f);
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    glm::mat4 proj = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(proj, glm::vec3(screenWidth/2, screenHeight/2, 0));

    glm::mat4 tran = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 rot = glm::rotate(tran, 45.0f, glm::vec3(0,0,1));
    glm::mat4 scale = glm::scale(rot, glm::vec3(100.0f));

    glm::mat4 model = scale;

    glm::mat4 mvp = model;

    float positions[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f, 1.0f,
        -1.0f, 1.0f
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
    
    int color = glGetUniformLocation(shader, "u_Color");
    int uMVP = glGetUniformLocation(shader, "u_MVP");

    glUniformMatrix4fv(uMVP, 1, GL_FALSE, &mvp[0][0]);

    float a = 0;
    float x = 0, y = 0;
    float s = 100.0f;

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); WIREFRAME

    // Main Loop
    while(engine->EngineRunning())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        tran = glm::translate(view, glm::vec3(-300.0f, y, 0.0f));
        rot = glm::rotate(tran, a, glm::vec3(0,0,-1));
        scale = glm::scale(rot, glm::vec3(s));

        model = scale;

        glUniformMatrix4fv(uMVP, 1, GL_FALSE, &model[0][0]);
        
        glUniform4f(color, 0.1, 0.8, 0.6, 1.0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


        tran = glm::translate(view, glm::vec3(300.0f, 0.0f, 0.0f));
        rot = glm::rotate(tran, -a, glm::vec3(0,0,-1));
        scale = glm::scale(rot, glm::vec3(100));

        model = scale;

        glUniformMatrix4fv(uMVP, 1, GL_FALSE, &model[0][0]);
        
        glUniform4f(color, 0.1, 0.8, 0.6, 1.0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        engine->SwapGLBuffers();

        if(aHeld) a += 0.01f;
    }

    return 0;
}