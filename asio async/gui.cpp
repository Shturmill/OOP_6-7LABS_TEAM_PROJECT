#include "gui.h"
#include "dns_resolver.h"
#include <boost/asio.hpp>
#include <iostream>
#include <string>

GUI::GUI(HINSTANCE hInstance) : hInstance_(hInstance), hwndMain_(nullptr) {}

GUI::~GUI() {}

void GUI::createMainWindow() {
    WNDCLASS wc = {};
    wc.lpfnWndProc = GUI::WindowProc;
    wc.hInstance = hInstance_;
    wc.lpszClassName = "DNSResolverWindow";

    RegisterClass(&wc);

    hwndMain_ = CreateWindowEx(
        0, "DNSResolverWindow", "DNS Resolver", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        nullptr, nullptr, hInstance_, nullptr);

    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        20, 20, 300, 25, hwndMain_, (HMENU)1, hInstance_, nullptr);

    CreateWindow("BUTTON", "Resolve", WS_CHILD | WS_VISIBLE,
        330, 20, 50, 25, hwndMain_, (HMENU)2, hInstance_, nullptr);

    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_READONLY,
        20, 60, 360, 180, hwndMain_, (HMENU)3, hInstance_, nullptr);

    ShowWindow(hwndMain_, SW_SHOW);
}

int GUI::run() {
    createMainWindow();

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK GUI::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hInput, hOutput;

    switch (uMsg) {
    case WM_CREATE:
        hInput = GetDlgItem(hwnd, 1);
        hOutput = GetDlgItem(hwnd, 3);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 2) {
            char buffer[256];
            GetWindowText(hInput, buffer, sizeof(buffer));
            std::string host(buffer);
            resolveDNS(host, hOutput);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void GUI::resolveDNS(const std::string& host, HWND output) {
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::resolver resolver(io_service);

    try {
        boost::asio::ip::tcp::resolver::query query(host, "http");
        auto results = resolver.resolve(query);

        std::string ip_list;
        for (const auto& entry : results) {
            ip_list += entry.endpoint().address().to_string() + "\r\n";
        }
        SetWindowText(output, ip_list.c_str());
    }
    catch (const std::exception& ex) {
        SetWindowText(output, ex.what());
    }
}
