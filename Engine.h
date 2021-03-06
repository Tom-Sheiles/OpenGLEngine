#pragma once
#include <Windows.h>

#define CREATE_CONSOLE 0x01

extern bool Keys[127];
extern bool Mouse[3];

class Engine{
private:
    HWND m_Hwnd;
    const wchar_t* m_WindowName;
    int m_Width, m_Height;

    MSG m_msg;

    static LRESULT CALLBACK SystemMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
    static LRESULT WindowDestroy(HWND hwnd);
    static LRESULT WindowCreate(HWND hwnd);

public:
    Engine(const wchar_t* WindowName, int x, int y, int width, int height, HINSTANCE hInstance, int options);
    ~Engine();

    static float deltaTime;

    bool EngineRunning();
    void SwapGLBuffers();

    void SetWindowTitle(const char* title);
};  