#ifndef UNICODE
#define UNICODE
#endif

#include "Engine.h"
#include <gl/glew.h>
#include <gl/GL.h>

#include "Quad.h"
#include "Renderer.h"
#include "Material.h"

#include <Windows.h>
#include <iostream>
#include <stdio.h>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    float screenWidth = 1280;
    float screenHeight = 720;

    Engine *engine = new Engine(L"APP", 320, 150, screenWidth, screenHeight, hInstance, CREATE_CONSOLE);
    Renderer::Init(screenWidth, screenHeight, engine);
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    Material *blue = new Material(STANDARD_SHADER);
    blue->SetColor("u_Color", 0, 0, 255, 255);

    Quad *quad = new Quad(blue);


    // Main Loop
    while(engine->EngineRunning())
    {
        Renderer::Draw();

        quad->rotation.z += 0.01f;
    }

    delete engine;

    return 0;
}