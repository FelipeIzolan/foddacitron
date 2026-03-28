#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#include "ini.h"

typedef enum {
  TOP_LEFT,
  TOP_CENTER,
  TOP_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_CENTER,
  BOTTOM_RIGHT
} align_t;

typedef struct { 
  //[windows]
  bool tray;
  align_t align;

  //[system]
  bool random; 
  uint8_t timer;
  const char * image;
  const char * sound;
  const char * path_to_images;
  const char * path_to_sounds;
} config_t;

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


bool atob(const char * str) { 
  if (strcmpi(str, "true") == 0)
    return true; 
  return false; 
}

align_t atoa(const char * str) {
  if (strcmpi(str, "top-left") == 0)
    return TOP_LEFT;
  if (strcmpi(str, "top-center") == 0)
    return TOP_CENTER; 
  if (strcmpi(str, "top-right") == 0)
    return TOP_RIGHT;
  if (strcmpi(str, "bottom-left") == 0)
    return BOTTOM_LEFT;
  if (strcmpi(str, "bottom-center") == 0)
    return BOTTOM_CENTER;
  return BOTTOM_RIGHT;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
  return DefWindowProc(hWnd, Message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE phInstance, LPSTR CmdLine, int CmdShow) {
  ini_t * ini = ini_load("config.ini");
  config_t config;

  //[windows]
  config.tray = atob(ini_get(ini, "windows", "tray"));
  config.align = atoa(ini_get(ini, "windows", "align"));
  //[system]
  config.random = atob(ini_get(ini, "system", "random"));
  config.timer = (uint8_t) atoi(ini_get(ini, "system", "timer"));
  if (!config.random) {
    config.image = ini_get(ini, "system", "image");
    config.sound = ini_get(ini, "system", "sound");
  }
  config.path_to_images = ini_get(ini, "system", "path_to_images");
  config.path_to_sounds = ini_get(ini, "system", "path_to_sounds");

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
  ini_free(ini);
  
  return EXIT_SUCCESS;
}
