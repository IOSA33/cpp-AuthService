#include "AuthService.h"
#include <iostream>
#include <string>
#include <algorithm>

void AuthService::run() {
    std::cout << "For Register enter: Email and Password!" << '\n';
    std::string input{};
    std::getline(std::cin >> std::ws, input);
    
    if (!input.empty()) {
        if (parser(input)) {
            // First param is email and the second is the pass
            m_storage.addUser(m_currentLine[0], m_currentLine[1]);
        } else {
            std::cout << "Email or Password is Incorrect Try again!" << '\n';
        }
    }
}

bool AuthService::parser(const std::string& input) {
    std::string temp{};
    for (const auto& i : input) {
        if (i != ' ') {
            temp.push_back(i);
        } else {
            m_currentLine.emplace_back(temp);
            temp.clear();
        }
    }

    if (!temp.empty()) {
        m_currentLine.emplace_back(temp);
    }

    // early return if user input is more than a 2 words
    if (m_currentLine.size() > 2) {
        return false;
    }

    if (m_currentLine[0].contains('@') && m_currentLine.size() == 2) {
        return true;
    }

    return false;
}