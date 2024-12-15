#include "dns_resolver.h"
#include <iostream>
#include <thread>

// Конструктор и деструктор для DNSResolver
DNSResolver::DNSResolver() : resolver_(io_service_) {}
DNSResolver::~DNSResolver() {}

// Асинхронное разрешение DNS
void DNSResolver::resolveHostAsync(const std::string& host, const std::string& service) {
    // Создание запроса на разрешение хоста
    boost::asio::ip::tcp::resolver::query query(host, service);

    // Асинхронное выполнение запроса
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

    // Запуск обработки асинхронных операций в отдельном потоке
    std::thread io_thread([this]() { io_service_.run(); });
    io_thread.detach();
}

// Внешняя функция для удобного вызова
void resolveDNSAsync(const std::string& host) {
    DNSResolver resolver;
    resolver.resolveHostAsync(host);
}
