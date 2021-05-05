#include "Engine.h"
#include "Renderer2D.h"
#include <Windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    float screenWidth = 800;
    float screenHeight = 600;

    Engine engine(L"APP", 200, 50, screenWidth, screenHeight, hInstance, CREATE_CONSOLE);
    Renderer2D::Init(screenWidth, screenHeight, &engine);

    while(engine.EngineRunning())
    {

        Renderer2D::Draw();
    }

    return 0;
}