#include <fstream>
#include <chrono>
#include <iostream>
#include <string>
#include <print>
#include "Logger.h"

void Logger::writeToFile(const std::string& typeCommand, const std::string& email) {
    std::ofstream file { m_path, std::ios_base::app };

    if (!file.is_open()) {
        std::cout << "Cannot open a file!\n"; 
        return;
    }

    const auto now = std::chrono::system_clock::now();
    auto zt_local = std::chrono::zoned_time{ std::chrono::current_zone(), now };
    std::print("Command: {}, was written for a {}, at {}\n", typeCommand, email, zt_local);

    file << typeCommand << " " << email << " " << zt_local << '\n';

    file.close();
}