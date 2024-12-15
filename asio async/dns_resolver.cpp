#include "dns_resolver.h"
#include <iostream>
#include <thread>

// ����������� � ���������� ��� DNSResolver
DNSResolver::DNSResolver() : resolver_(io_service_) {}
DNSResolver::~DNSResolver() {}

// ����������� ���������� DNS
void DNSResolver::resolveHostAsync(const std::string& host, const std::string& service) {
    // �������� ������� �� ���������� �����
    boost::asio::ip::tcp::resolver::query query(host, service);

    // ����������� ���������� �������
    resolver_.async_resolve(query,
        [this, host](const boost::system::error_code& ec, auto results) {
            if (!ec) {
                std::cout << "DNS results for " << host << ":\n";
                for (const auto& entry : results) {
                    std::cout << entry.endpoint().address().to_string() << "\n";
                }
            }
            else {
                std::cerr << "Failed to resolve host: " << ec.message() << std::endl;
            }
        });

    // ������ ��������� ����������� �������� � ��������� ������
    std::thread io_thread([this]() { io_service_.run(); });
    io_thread.detach();
}

// ������� ������� ��� �������� ������
void resolveDNSAsync(const std::string& host) {
    DNSResolver resolver;
    resolver.resolveHostAsync(host);
}
