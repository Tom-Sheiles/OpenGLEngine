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
#include <chrono>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    float screenWidth = 1280;
    float screenHeight = 720;

    Engine *engine = new Engine(L"APP", 320, 150, screenWidth, screenHeight, hInstance, 0);
    Renderer::Init(screenWidth, screenHeight, engine);
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    Material *greenBlue = new Material(STANDARD_SHADER);
    greenBlue->SetColor("u_Color", 86, 227, 159, 255);
    Material *red = new Material(STANDARD_SHADER);
    red->SetColor("u_Color", 239, 111, 108, 255);

    float x = -6.0f;
    float y = 3.1f;

    std::vector<Object*> objects;
    Quad *quad;

    for(int j = 0; j < 100; j++){
        x = -6.0f;
        for(int i = 0; i < 16; i++)
        {
            if(j == 3 && i == 5) quad = new Quad(greenBlue);
            else quad = new Quad(red);
            quad->position.x = x;
            quad->position.y = y;
            //quad->position.z = -3;
            quad->scale = {0.3f, 0.3f, 1};
            x += 0.8f;
            objects.push_back(quad);
        }
        y-=0.8f;
    }

    int objectCount = objects.size();
    int verts = objects.size() * 6;

    auto tp1 = std::chrono::system_clock::now();
    auto tp2 = std::chrono::system_clock::now();
    float fps = 0;

    int ticks = 0;

    // Main Loop
    while(engine->EngineRunning())
    {
        ticks++;

        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float deltaTime = elapsedTime.count();

        if(ticks > 1000){
            fps = 1.0f / deltaTime;

            char buffer[255];
            snprintf(buffer, sizeof buffer, "FPS: %3.2f Object Count: %d Verts: %d", fps, objectCount, verts);
            engine->SetWindowTitle(buffer);
            ticks = 0;
        }

        for(int i = 0; i < objects.size(); i++)
        {
            objects[i]->rotation.z += 0.5f * deltaTime;
        }

        Renderer::Draw();
    }

    delete engine;

    return 0;
}