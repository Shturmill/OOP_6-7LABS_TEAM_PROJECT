#pragma once

#include <winsock2.h>
#define _WINSOCKAPI_
#include <windows.h>
#include "dns_resolver.h"

class GUI {
public:
    GUI(HINSTANCE hInstance);
    ~GUI();

    // ������ �������� ����
    void Run();

private:
    HINSTANCE hInstance_;
    HWND hwndMain_;
    HWND hwndInput_;
    HWND hwndOutput_;
    HWND hwndButton_;

    // ���������� ������� ���������
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    // ��������� �������� � GUI
    void OnResolveClicked();
};