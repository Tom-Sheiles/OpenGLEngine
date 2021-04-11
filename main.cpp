#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>

LRESULT CALLBACK SystemMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t className[] = L"Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = SystemMessage;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        CS_OWNDC,
        className,
        L"Window",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if(hwnd == NULL){ return -1; }
    ShowWindow(hwnd, nCmdShow);
    MSG msg = {};

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK OnCreate(HWND hwnd)
{
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
    };

    HDC windowContext = GetDC(hwnd);
    int pixelFormat;
    pixelFormat = ChoosePixelFormat(windowContext, &pfd);
    SetPixelFormat(windowContext, pixelFormat, &pfd);

    HGLRC OpenGlContext = wglCreateContext(windowContext);
    wglMakeCurrent(windowContext, OpenGlContext);

    MessageBoxA(0, (char*)glGetString(GL_VERSION), "OpenGL Version", 0);
    return 0;
}

LRESULT CALLBACK SystemMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
        case WM_DESTROY:  PostQuitMessage(0); return 0;
        case WM_CREATE:   return OnCreate(hwnd);
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}