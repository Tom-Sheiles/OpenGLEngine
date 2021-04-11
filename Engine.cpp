#ifndef UNICODE
#define UNICODE
#endif

#include "Engine.h"
#include <GL/glew.h>
#include <Windows.h>
#include <stdio.h>

LRESULT Engine::WindowDestroy(HWND hwnd)
{
    DestroyWindow(hwnd);
    PostQuitMessage(0);
    return 0;
}

LRESULT Engine::WindowCreate(HWND hwnd)
{
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd  
        1,                     // version number  
        PFD_DRAW_TO_WINDOW |   // support window  
        PFD_SUPPORT_OPENGL |   // support OpenGL  
        PFD_DOUBLEBUFFER,      // double buffered  
        PFD_TYPE_RGBA,         // RGBA type  
        24,                    // 24-bit color depth  
        0, 0, 0, 0, 0, 0,      // color bits ignored  
        0,                     // no alpha buffer  
        0,                     // shift bit ignored  
        0,                     // no accumulation buffer  
        0, 0, 0, 0,            // accum bits ignored  
        32,                    // 32-bit z-buffer      
        0,                     // no stencil buffer  
        0,                     // no auxiliary buffer  
        PFD_MAIN_PLANE,        // main layer  
        0,                     // reserved  
        0, 0, 0
    };

    HDC hdc = GetDC(hwnd);
    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixelFormat, &pfd);

    HGLRC RenderingContext = wglCreateContext(hdc);
    wglMakeCurrent(hdc, RenderingContext);

    if(glewInit() != GLEW_OK)
    {
        printf("Glew could not be loaded\n");
    }
    else{
        printf("OpenGl Extension Library loaded successfully\n");
    }

    return 0;
}


LRESULT CALLBACK Engine::SystemMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
    switch (msg)
    {
        case WM_CLOSE:    return Engine::WindowDestroy(hwnd);
        case WM_DESTROY:  PostQuitMessage(0); return 0;
        case WM_CREATE:   return Engine::WindowCreate(hwnd);
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

bool Engine::EngineRunning()
{
    while(PeekMessage(&m_msg, 0, 0, 0, PM_REMOVE))
    {
        if(m_msg.message == WM_QUIT) return false;
        TranslateMessage(&m_msg);
        DispatchMessage(&m_msg);
    }

    return true;
}

void Engine::SwapGLBuffers()
{
    HDC hdc = GetDC(m_Hwnd);
    SwapBuffers(hdc);
}

Engine::Engine(const wchar_t* WindowName, int x, int y, int width, int height, HINSTANCE hInstance, int options = 0)
    :m_WindowName(WindowName), m_Width(width), m_Height(height)
{

    if((options & CREATE_CONSOLE) == CREATE_CONSOLE){
        int res = AllocConsole();
        if(res)
        {
            freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
            HWND console = GetConsoleWindow();
            SetWindowPos(console, 0, 0, 100, 0, 0, SWP_NOSIZE);
        }
    }

    STARTUPINFO si;
    GetStartupInfo(&si);
    int cmd = si.wShowWindow;

    const wchar_t className[] = L"Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = Engine::SystemMessage;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wc.style = CS_OWNDC;

    RegisterClass(&wc);

    if(!(m_Hwnd = CreateWindow(className,WindowName,WS_OVERLAPPEDWINDOW | WS_VISIBLE,x, y, m_Width, m_Height,0, 0,hInstance,0)))
    {
        MessageBoxA(0, "Could not Create Window", "wMCreateWindow() Error in engine", 0);
    }
    m_msg = {0};
}

Engine::~Engine(){

}