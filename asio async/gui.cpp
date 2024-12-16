#include <winsock2.h>  // Подключить winsock2.h первым
#define _WINSOCKAPI_    // Предотвращает подключение устаревшего winsock.h
#include <windows.h>
#include "gui.h"
#include <sstream>


GUI::GUI(HINSTANCE hInstance) : hInstance_(hInstance), hwndMain_(nullptr), hwndInput_(nullptr), hwndOutput_(nullptr), hwndButton_(nullptr) {}

GUI::~GUI() {}

void GUI::Run() {
    // Регистрация класса окна
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance_;
    wc.lpszClassName = L"DNSResolverGUI";
    RegisterClass(&wc);

    // Создание главного окна
    hwndMain_ = CreateWindow(
        L"DNSResolverGUI",
        L"DNS Resolver",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        nullptr, nullptr, hInstance_, this
    );

    // Создание элементов интерфейса
    hwndInput_ = CreateWindow(
        L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 10, 300, 25,
        hwndMain_, nullptr, hInstance_, nullptr
    );

    hwndOutput_ = CreateWindow(
        L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
        10, 50, 360, 150,
        hwndMain_, nullptr, hInstance_, nullptr
    );

    hwndButton_ = CreateWindow(
        L"BUTTON", L"Resolve",
        WS_CHILD | WS_VISIBLE,
        320, 10, 60, 25,
        hwndMain_, (HMENU)1, hInstance_, nullptr
    );

    ShowWindow(hwndMain_, SW_SHOW);

    // Цикл обработки сообщений
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK GUI::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_CREATE) {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        GUI* pGUI = (GUI*)pcs->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pGUI);
        return 0;
    }

    GUI* pGUI = (GUI*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (pGUI) {
        switch (msg) {
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) { // Нажата кнопка "Resolve"
                pGUI->OnResolveClicked();
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        }
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void GUI::OnResolveClicked() {
    wchar_t hostBuffer[256];
    GetWindowText(hwndInput_, hostBuffer, 256);

    std::wstring host(hostBuffer);
    if (host.empty()) {
        SetWindowText(hwndOutput_, L"Please enter a DNS name.");
        return;
    }

    DNSResolver resolver;
    resolver.resolveHostAsync(std::string(host.begin(), host.end()));

    SetWindowText(hwndOutput_, L"Resolving... (check console for results)");
}
