#include "AuthService.h"
#include <iostream>
#include <string>
#include <algorithm>

void AuthService::run() {
    while (true) {
        std::cout << "\nCommands:" << '\n';
        std::cout << "1) REG [EMAIL] [PASSWORD]" << '\n';
        std::cout << "2) LOG [EMAIL] [PASSWORD]" << '\n';
        
        m_currentLine.clear();
        std::string input{};
        std::getline(std::cin >> std::ws, input);

        if (input == "exit") return;

        if (!input.empty()) {
            if (parser(input)) {
                if (m_currentLine[0] == "REG") {
                    if (m_storage.addUser(m_currentLine[1], m_currentLine[2])) {
                        std::cout << "Congrats! User registered!\n";
                        std::string curr_session { m_storage.createSessionID() };
                        if (curr_session.empty()) {
                            std::cout << "Something went wrong!\n";
                            continue;
                        }

                        std::cout << curr_session << std::endl;

                    } else {
                        continue;
                    }

                } else if (m_currentLine[0] == "LOG") {
                    if (m_storage.verifyUser(m_currentLine[1], m_currentLine[2])) {
                        std::cout << "Congrats! User logged in!\n";
                        std::string curr_session { m_storage.createSessionID() };
                        if (curr_session.empty()) {
                            std::cout << "Something went wrong!\n";
                            continue;
                        }

                        std::cout << curr_session << std::endl;

                    } else {
                        continue;
                    }

                } else {
                    std::cout << "Unknown Command try again!" << '\n';
                    continue;
                }

            } else {
                std::cout << "Input is Incorrect. Try again!" << '\n';
            }
            
        } else {
            std::cout << "Input is empty!" << '\n';
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

    if (m_currentLine.size() > 2) {
        if (m_currentLine[1].contains('@') && m_currentLine[1].contains('.') && m_currentLine.size() == 3) {
            return true;
        }        
    }
 
    return false;
}