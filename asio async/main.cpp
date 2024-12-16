#include "gui.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    GUI gui(hInstance);
    gui.Run();
    return 0;
}
