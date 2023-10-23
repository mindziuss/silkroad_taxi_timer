// silkroad_taxi_timer.cpp : Defines the entry point for the application.
//
#include <Dwmapi.h>
#include "framework.h"
#include "silkroad_taxi_timer.h"

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR overlayTitle[100] = L"Overlay";                  // The title bar txt
LPCSTR targetWindow = "Origin Online | Genesis | [Lapinas]";
int width, height, x ,y;
HWND overlayHWND, targetHWND;
Paint paint;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MyRegisterClass(hInstance);

    targetHWND = FindWindowA(0, targetWindow);

    //calc size of window
    if (targetHWND) {
        RECT rect;

        GetWindowRect(targetHWND, &rect);

        width = rect.right - rect.left;
        height = rect.bottom - rect.top ;
    }
    else {
        return FALSE;
    }
    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    paint = Paint(overlayHWND, targetHWND, width, height);
    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        RECT rect;

        GetWindowRect(targetHWND, &rect);
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;
        
       // SetWindowPos(overlayHWND, HWND_TOPMOST, rect.left, rect.top, 0, 0, 0);


        MoveWindow(overlayHWND, rect.left, rect.top, width, height, true);
    }

    return (int) msg.wParam;
}
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = 0;
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground  = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpszMenuName   = overlayTitle;
    wcex.lpszClassName  = overlayTitle;
    wcex.hIconSm        = 0;

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    overlayHWND = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED , overlayTitle, overlayTitle, WS_POPUP,
      1, 1, width, height, nullptr, nullptr, hInstance, nullptr);

   if (!overlayHWND)
   {
      return FALSE;
   }
   SetLayeredWindowAttributes(overlayHWND, RGB(0, 0, 0), 0, LWA_COLORKEY);

   ShowWindow(overlayHWND, nCmdShow);
   //UpdateWindow(overlayHWND);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND overlayHWND, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        paint.render();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(overlayHWND, message, wParam, lParam);
    }
    return 0;
}
