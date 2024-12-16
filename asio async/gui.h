#pragma once

#include <winsock2.h>
#define _WINSOCKAPI_
#include <windows.h>
#include "dns_resolver.h"

class GUI {
public:
    GUI(HINSTANCE hInstance);
    ~GUI();

    // Запуск главного окна
    void Run();

private:
    HINSTANCE hInstance_;
    HWND hwndMain_;
    HWND hwndInput_;
    HWND hwndOutput_;
    HWND hwndButton_;

    // Обработчик оконных сообщений
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    // Обработка действий в GUI
    void OnResolveClicked();
};