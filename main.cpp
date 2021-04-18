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
    float nearPlane = -0.3f;
    float farPlane = 1000.0f;

    Engine *engine = new Engine(L"APP", 200, 50, screenWidth, screenHeight, hInstance, CREATE_CONSOLE);
    //Renderer::Init(screenWidth, screenHeight, engine, SHADED | CULLING);

    Renderer2D::Init(screenWidth, screenHeight, engine);

    while(engine->EngineRunning())
    {

        Renderer2D::Draw();
    }

    delete engine;
    //delete shader;

    return 0;
}