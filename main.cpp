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

    Engine *engine = new Engine(L"APP", 0, 20, screenWidth, screenHeight, hInstance, CREATE_CONSOLE);
    Renderer::Init(screenWidth, screenHeight, engine, WIREFRAME | CULLING);

    Material *red = new Material();
    red->SetColor("u_Color", 200, 50, 50, 255);

    Quad *quad = new Quad(red);
    quad->position = {0, 0, -5.0f};
    quad->scale = {0.5f, 0.5f, 0.5f};

    float speed = 5;

    // Main Loop
    while(engine->EngineRunning())
    {
        if(Keys['Q']) quad->position.y += 1.0f *speed* Engine::deltaTime;
        if(Keys['E']) quad->position.y -= 1.0f *speed* Engine::deltaTime;
        if(Keys['A']) quad->position.x -= 1.0f *speed* Engine::deltaTime;
        if(Keys['D']) quad->position.x += 1.0f *speed* Engine::deltaTime;
        if(Keys['S']) quad->position.z += 1.0f *speed* Engine::deltaTime;
        if(Keys['W']) quad->position.z -= 1.0f *speed* Engine::deltaTime;

        Renderer::Draw();
    }

    delete engine;

    return 0;
}