#include <windows.h>
#include <gdiplus.h>
#include <wchar.h>

#include <iostream>

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param,
                                       LPARAM lparam);
void draw(HDC hdc, PAINTSTRUCT ps);

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance,
                   PSTR cmdLine, INT cmdCount) {
  // Initialize GDI+
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;
  Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

  // Register The Window Class
  const char* CLASS_NAME = "Win32WindowClass";
  WNDCLASS wc{};
  wc.hInstance = currentInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.lpfnWndProc = WindowProcessMessages;
  RegisterClass(&wc);

  // Create The Window
  HWND hwnd = CreateWindow(CLASS_NAME, "Win32 Window",
               WS_OVERLAPPEDWINDOW | WS_VISIBLE,  // Window Style
               CW_USEDEFAULT, CW_USEDEFAULT,      // Window Position
               800, 600,                          // Window Size
               nullptr, nullptr, nullptr, nullptr);

ShowWindow(hwnd, cmdCount);
  // Window Loop
  MSG msg{};
  while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);

    if (GetKeyState(VK_END) & 0x8000) {
        PostQuitMessage(0);
    }
  }

  Gdiplus::GdiplusShutdown(gdiplusToken);
  return 0;
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT uMsg, WPARAM param,
                                       LPARAM lparam) {
    wchar_t msg[32];

    HDC hdc;
    PAINTSTRUCT ps;

    switch (uMsg) {
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            // draw. . .
            draw(hdc, ps);

            EndPaint(hwnd, &ps);
            break;

        case WM_SYSKEYDOWN:
            swprintf_s(msg, L"WM_SYSKEYDOWN: 0x%x\n", param);
            OutputDebugString((LPCSTR)msg);
            break;

        case WM_SYSCHAR:
            swprintf_s(msg, L"WM_SYSCHAR: %c\n", (wchar_t)param);
            OutputDebugString((LPCSTR)msg);
            break;

        case WM_SYSKEYUP:
            swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", param);
            OutputDebugString((LPCSTR)msg);
            break;

        case WM_KEYDOWN:
            swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", param);
            OutputDebugString((LPCSTR)msg);
            break;

        case WM_KEYUP:
            swprintf_s(msg, L"WM_KEYUP: 0x%x\n", param);
            OutputDebugString((LPCSTR)msg);
            break;

        case WM_CHAR:
            swprintf_s(msg, L"WM_CHAR: %c\n", (wchar_t)param);
            OutputDebugString((LPCSTR)msg);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
      return DefWindowProc(hwnd, uMsg, param, lparam);
}

void draw(HDC hdc, PAINTSTRUCT ps) {
    Gdiplus::Graphics gf(hdc);
    Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));           // ARGB; Red
    Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 255, 0));  // ARGB; Green

    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));

    /*gf.DrawLine(&pen, 0, 0, 500, 500);
    gf.FillRectangle(&brush, 400, 200, 100, 100);
    gf.DrawRectangle(&pen, 400, 400, 100, 150);

    // Not Working?
    Gdiplus::Bitmap bmp(L"GitlabVR.PNG");
    gf.DrawImage(&bmp, 430, 10);

    gf.FillEllipse(&brush, 50, 400, 100, 100); */
}