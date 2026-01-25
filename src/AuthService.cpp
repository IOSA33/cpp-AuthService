#include "AuthService.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <print>
#include "Logger/Logger.h"
#include "Config/Config.h"

// Commands
// REG [email] [pass] : return sessionID
// LOG [email] [pass] : return sessionID
// GET [sessionID] : if sessionID exists returns value of it, otherwise null
// UPDATE [EMAIL] [OLD_PASS] [NEW_PASS] : updates current password
// DELETE [EMAIL] [PASSWORD] : deleted every sessionID that user has
// LOGOUT [EMAIL] [sessionID] : deletes sessionID

// Just for local run without server
void AuthService::run() {
    while (true) {
        std::cout << "\nCommands:" << '\n';
        std::cout << "1) REG [EMAIL] [PASSWORD]" << '\n';
        std::cout << "2) LOG [EMAIL] [PASSWORD]" << '\n';
        std::cout << "3) GET [sessionID]" << '\n';
        std::cout << "4) UPDATE [EMAIL] [OLD_PASS] [NEW_PASS]" << '\n';
        std::cout << "5) DELETE [EMAIL] [PASSWORD]" << '\n';
        std::cout << "6) LOGOUT [EMAIL] [sessionID]" << '\n';

        m_currentLine.clear();
        std::string input{};
        std::getline(std::cin >> std::ws, input);

        if (input == "exit") return;

        if (!input.empty()) {
            if (parser(input)) {
                if (m_currentLine[0] == "REG") {
                    if (m_storage.addUser(m_currentLine[1], m_currentLine[2])) {
                        std::cout << "Congrats! User registered!\n";
                        std::cout << m_storage.createSessionID(m_currentLine[1], m_config->auth.access_ttl) << '\n';
                        writeLogCMD();
                        continue;
                    } else {
                        continue;
                    }
                }

                if (m_currentLine[0] == "LOG") {
                    if (m_storage.verifyUser(m_currentLine[1], m_currentLine[2])) {
                        std::cout << "Congrats! User logged in!\n";
                        std::cout << m_storage.createSessionID(m_currentLine[1], m_config->auth.access_ttl) << '\n';
                        writeLogCMD();
                        continue;
                    } else {
                        continue;
                    }
                }

                if (m_currentLine[0] == "UPDATE") {
                    if (m_storage.updateUserPass(m_currentLine[1], m_currentLine[2], m_currentLine[3])) {
                        std::cout << "Congrats! User UPDATED!\n";
                        // Firstly we revoke all old sessionid of the user
                        m_storage.revokeAllSessionID(m_currentLine[1]);
                        // Then we create new one
                        std::cout << m_storage.createSessionID(m_currentLine[1], m_config->auth.access_ttl) << '\n';
                        writeLogCMD();
                        continue;
                    } else {
                        continue;
                    }
                }

                if (m_currentLine[0] == "DELETE") {
                    if (m_storage.deleteUser(m_currentLine[1], m_currentLine[2])) {
                        std::cout << "Congrats! User DELETED!\n";
                        // Firstly we revoke all old sessionid of the user
                        m_storage.revokeAllSessionID(m_currentLine[1]);
                        writeLogCMD();
                        continue;
                    } else {
                        continue;
                    }
                }

                if (m_currentLine[0] == "LOGOUT") {
                    if (m_storage.checkEmail(m_currentLine[1])) {
                        // Revoking sessionId
                        if (m_storage.revokeSessionID(m_currentLine[2])) {
                            std::cout << "Congrats! User lOGOUT!\n";
                            writeLogCMD();
                        } else {
                            std::cout << "Invalid sessionID!" << '\n';
                        }
                        
                        continue;
                    } else {
                        continue;
                    }
                }

                // Returns value of the session
                if (m_currentLine[0] == "GET") {
                    std::string result{ m_storage.getDataSessionID(m_currentLine[1]) }; 

                    if (result.empty()) {
                        std::cout << "No value!" << '\n';
                        continue;
                    }

                    // After every success of getting data we refreshing current sessionId
                    // m_storage.refreshSessionID(m_currentLine[1], m_config->auth.refresh_ttl);

                    std::cout << "GET some result!" << '\n';
                    continue;
                }
                
                std::cout << "Input is Incorrect. Try again!" << '\n';

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

    if(m_currentLine[0] == "GET" && m_currentLine.size() == 2) return true;
    
    if (m_currentLine.size() >= 3 && m_currentLine[1].contains('@') && m_currentLine[1].contains('.')) {
        if (m_currentLine[0] == "REG" && m_currentLine.size() == 3) return true;
        if(m_currentLine[0] == "LOG" && m_currentLine.size() == 3) return true;
        if(m_currentLine[0] == "DELETE" && m_currentLine.size() == 3) return true;
        if(m_currentLine[0] == "UPDATE" && m_currentLine.size() == 4) return true;
        if(m_currentLine[0] == "LOGOUT" && m_currentLine.size() == 3) return true;
    }
 
    return false;
}

void AuthService::writeLogCMD() {
    const std::string op { "AuthService::writeLogCMD()" };
    if (m_logger) {
        m_logger->writeToFile(m_currentLine[0], m_currentLine[1]);
    } else {
        std::print("{} ptr is null", op);
    }
}