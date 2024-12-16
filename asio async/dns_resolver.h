#pragma once

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <windows.h>

class DNSResolver {
public:
    DNSResolver();
    ~DNSResolver();

    void setOutputHandle(HWND hwnd);
    void resolveHostAsync(const std::string& host, const std::string& service = "");
    const std::vector<std::wstring>& getResults() const; // Метод для получения сохранённых результатов

private:
    std::wstring convertToWString(const std::string& str);

    std::vector<std::wstring> dnsResults_; // Для хранения всех разрешённых адресов
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::resolver resolver_;
    std::thread io_thread_;
    HWND hwndOutput_; // Хэндл окна для вывода результатов
};