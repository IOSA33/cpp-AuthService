#pragma once

#include <vector>
#include <string>
#include "Storage/Storage.h"

class Logger;

class AuthService{
private:
    // TODO: Should read from cfg file;
    Storage m_storage{"dbname = postgres user = postgres password = 1234 \
             hostaddr = 127.0.0.1 port = 5432"};

    // TODO: Logger
    Logger* m_logger{};
    std::vector<std::string> m_currentLine{};

public:
    // TODO: Constuctor with cfg reader
    AuthService(Logger* logger = nullptr) 
        : m_logger(logger) {}
    ~AuthService() {}

    void run();
    bool parser(const std::string& input);
};