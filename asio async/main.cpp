#include "dns_resolver.h"
#include <iostream>
#include <string>
#include <thread>

int main() {
    std::string host;
    std::cout << "Enter the DNS: ";
    std::cin >> host;

    // ������ ������������ ���������� DNS
    resolveDNSAsync(host);

    return 0;
}