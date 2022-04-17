#include <windows.h>
#include <gdiplus.h>

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param,
                                       LPARAM lparam);
void draw(HDC hdc);

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
  CreateWindow(CLASS_NAME, "Win32 Window",
               WS_OVERLAPPEDWINDOW | WS_VISIBLE,  // Window Style
               CW_USEDEFAULT, CW_USEDEFAULT,      // Window Position
               800, 600,                          // Window Size
               nullptr, nullptr, nullptr, nullptr);

  // Window Loop
  MSG msg{};
  while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  Gdiplus::GdiplusShutdown(gdiplusToken);
  return 0;
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param,
                                       LPARAM lparam) {
  HDC hdc;
  PAINTSTRUCT ps;

  switch (msg) {
    case WM_PAINT:
      hdc = BeginPaint(hwnd, &ps);
      // draw. . .
      draw(hdc);

      EndPaint(hwnd, &ps);
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    default:
      return DefWindowProc(hwnd, msg, param, lparam);
  }
}

void draw(HDC hdc) {
  Gdiplus::Graphics gf(hdc);
  Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));           // ARGB; Red
  Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 255, 0));  // ARGB; Green

  gf.DrawLine(&pen, 0, 0, 500, 500);
  gf.FillRectangle(&brush, 400, 200, 100, 100);
  gf.DrawRectangle(&pen, 400, 400, 100, 150);

  // Not Working?
  Gdiplus::Bitmap bmp(L"GitlabVR.PNG");
  gf.DrawImage(&bmp, 430, 10);

  gf.FillEllipse(&brush, 50, 400, 100, 100);
}