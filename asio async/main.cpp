#include "gui.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // �������� � ������ GUI
    GUI gui(hInstance);
    gui.Run();
    return 0;
}
