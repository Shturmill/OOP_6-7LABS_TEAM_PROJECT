#pragma once

#include <winsock2.h>
#define _WINSOCKAPI_
#include <windows.h>
#include <string>
#include <vector>
#include <boost/asio.hpp>

class DNSResolver {
public:
    DNSResolver();
    ~DNSResolver();

    // ����������� ���������� DNS
    void resolveHostAsync(const std::string& host, const std::string& service = "http");

private:
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::resolver resolver_;
};

// ������� ������� ��� �������� ������
void resolveDNSAsync(const std::string& host);