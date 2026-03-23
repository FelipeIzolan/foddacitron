#include <stdlib.h>
#include <windows.h>

void ShowLastError() {
  DWORD err = GetLastError();
  LPTSTR buf = NULL;

  FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
    NULL,
    err,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (LPTSTR) &buf,
    0,
    NULL
  );

  MessageBox(NULL, buf, NULL, MB_ICONERROR | MB_OK);
  LocalFree(buf);
}

LRESULT Wndproc(
  HWND unnamedParam1,
  UINT unnamedParam2,
  WPARAM unnamedParam3,
  LPARAM unnamedParam4
) {
  return 0;
}


int main() {
  HWND window;
  WNDCLASS class = {
    .style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW,
    .lpfnWndProc = Wndproc,
    .lpszClassName = "foddacitron",
    .hInstance = GetModuleHandle(NULL),
    .hCursor = LoadCursor(NULL, IDC_ARROW),
    .hIcon = LoadImage(
       NULL, 
      "assets/icon.ico",
      IMAGE_ICON, 
      0, 0, 
      LR_LOADFROMFILE
    )
  };
  
  if (class.hIcon == NULL) {
    MessageBox(NULL, "Load image (for icon) failed.", NULL, MB_ICONERROR | MB_OK);
    return EXIT_FAILURE;
  }

  if (RegisterClass(&class) == 0) {
    MessageBox(NULL, "Register class failed.", NULL, MB_ICONERROR | MB_OK);
    return EXIT_FAILURE;
  }

  window = CreateWindow(
    "foddacitron",
    "foddacitron",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    500,500,
    0,
    0,
    class.hInstance,
    0
  );

  if (window == NULL) {
    ShowLastError();
    MessageBox(NULL, "Create window failed.", NULL, MB_ICONERROR | MB_OK);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
