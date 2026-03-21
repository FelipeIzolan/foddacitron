#include <stdlib.h>
#include <windows.h>

int main() {
  WNDCLASSA class;

  class.lpszClassName = "foddacitron";
  class.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
  class.hIcon = LoadImageA(
    NULL, 
    "assets/icon.ico",
    IMAGE_ICON, 
    0, 0, 
    LR_LOADFROMFILE
  );

  RegisterClass(&class);


  UnregisterClass("foddacitron", NULL);
  
  return EXIT_SUCCESS;
}
