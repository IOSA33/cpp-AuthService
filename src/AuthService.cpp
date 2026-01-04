#include "AuthService.h"
#include <iostream>
#include <string>

void AuthService::run() {
    std::cout << "For Register enter: Username and Password!" << '\n';
    std::string input{};
    std::getline(std::cin >> std::ws, input);
    
    if (!input.empty()) {

    }

    // TODO: Request for the database
    m_storage.request(input);
}