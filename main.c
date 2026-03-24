#include <stdlib.h>
#include <windows.h>

// void ShowLastError() {
//   DWORD err = GetLastError();
//   LPTSTR buf = NULL;
// 
//   FormatMessage(
//     FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
//     NULL,
//     err,
//     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//     (LPTSTR) &buf,
//     0,
//     NULL
//   );
// 
//   MessageBox(NULL, buf, NULL, MB_ICONERROR | MB_OK);
//   LocalFree(buf);
// }


LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
  return DefWindowProc(hWnd, Message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE phInstance, LPSTR CmdLine, int CmdShow) {
  WNDCLASS wc = {
    .style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW,
    .lpfnWndProc = WndProc,
    .lpszClassName = "foddacitron",
    .hInstance = hInstance,
    .hCursor = LoadCursor(hInstance, IDC_ARROW),
    .hIcon = LoadImage(
       hInstance, 
      "assets/icon.ico",
      IMAGE_ICON, 
      0, 0, 
      LR_LOADFROMFILE
    ),
  };
  
  if (wc.hIcon == NULL) {
    MessageBox(NULL, "Load image (for icon) failed.", NULL, MB_ICONERROR | MB_OK);
    return EXIT_FAILURE;
  }

  if (!RegisterClass(&wc)) {
    MessageBox(NULL, "Register class failed.", NULL, MB_ICONERROR | MB_OK);
    return EXIT_FAILURE;
  }

  HWND hwnd = CreateWindow(
    wc.lpszClassName,
    "foddacitron",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    500,500,
    0,
    0,
    hInstance,
    0
  );

  if (hwnd == NULL) {
    MessageBox(NULL, "Create window failed.", NULL, MB_ICONERROR | MB_OK);
    return EXIT_FAILURE;
  }

  DestroyWindow(hwnd);
  UnregisterClass(wc.lpszClassName, wc.hInstance);

  return EXIT_SUCCESS;
}
