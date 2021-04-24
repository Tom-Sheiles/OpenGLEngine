#include "Engine.h"
#include <gl/glew.h>
#include <gl/GL.h>

#include "Quad.h"
#include "Renderer.h"
#include "Renderer2D.h"
#include "Material.h"

#include <Windows.h>
#include <iostream>
#include <stdio.h>

#include<array>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    float screenWidth = 800;
    float screenHeight = 600;

    Engine *engine = new Engine(L"APP", 200, 50, screenWidth, screenHeight, hInstance, CREATE_CONSOLE);
    //Renderer2D::Init(screenWidth, screenHeight, engine);

   float positions[] = {
        -0.5f, -0.5f, 0.0,    1.0, 0.0, 0.0,
         0.5f, -0.5f, 0.0,    0.0, 1.0, 0.0,
         0.5f, 0.5f, 0.0,     0.0, 0.0, 1.0,
        -0.5f, 0.5f, 0.0,     1.0, 1.0, 0.0,
    };

    unsigned int indicies[]{
        0, 1, 2,
        2, 3, 0
    };

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (const void*)(3*sizeof(float)));

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    Shader *shader = new Shader("./res/Shaders/UnlitVertex.GLSL", "./res/Shaders/UnlitFragment.GLSL");

    while(engine->EngineRunning())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        //Renderer2D::Draw();

        engine->SwapGLBuffers();
    }


    delete engine;
    return 0;
}