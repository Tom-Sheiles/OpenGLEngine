#ifndef UNICODE
#define UNICODE
#endif

#include "Engine.h"
#include <gl/glew.h>
#include <gl/GL.h>

#include <Windows.h>
#include <iostream>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    Engine *engine = new Engine(L"APP", 780, 250, 500, 500, hInstance, 0);

    glClearColor(1.0f, 0.5f, 0.85f, 1.0f);
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;


    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f, 0.5f
    };

    unsigned int indicies[]
    {
        0, 1, 2
    };

    unsigned int VertexBuffer;
    glGenBuffers(1, &VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), indicies, GL_STATIC_DRAW);

    // Main Loop
    while(engine->EngineRunning())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        engine->SwapGLBuffers();
    }

    return 0;
}