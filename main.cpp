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

struct Vertex{
    Vector3 position;
    Vector3 tint;
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    float screenWidth = 800;
    float screenHeight = 600;

    Engine *engine = new Engine(L"APP", 200, 50, screenWidth, screenHeight, hInstance, CREATE_CONSOLE);
    Renderer2D::Init(screenWidth, screenHeight, engine);

    while(engine->EngineRunning())
    {

        Renderer2D::Draw();
    }


    delete engine;
    return 0;
}