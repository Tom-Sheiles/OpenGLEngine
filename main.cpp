#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>

#include "Engine.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    Engine *engine = new Engine(L"APP", 0, 0, 500, 500, hInstance);

    glClearColor(1.0f, 0.5f, 0.85f, 1.0f);
    bool isRunning = false;

    while((isRunning = engine->EngineRunning()))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POLYGON);

        glVertex2f(-0.5f, -0.5f); glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f( 0.5f, -0.5f); glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f( 0.0f,  0.5f); glColor3f(0.0f, 0.0f, 1.0f);

        glEnd();

        engine->SwapGLBuffers();
    }

    return 0;
}