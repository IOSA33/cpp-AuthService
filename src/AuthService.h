#pragma once

#include <vector>
#include <string>
#include "Storage/Storage.h"

class Logger;
namespace ConfigSpace {
    class Config;
}

class AuthService{
private:
    Storage m_storage{ "dbname = postgres user = postgres password = 1234 \
             hostaddr = 127.0.0.1 port = 5432", 8080 };
    Logger* m_logger{};
    ConfigSpace::Config* m_config{};

    std::vector<std::string> m_currentLine{};
    
public:
    // TODO: Constuctor with cfg reader
    AuthService(Logger* logger = nullptr, ConfigSpace::Config* cfg = nullptr ) 
        : m_logger(logger), m_config(cfg) {}
    ~AuthService() {}

    void run();
    bool parser(const std::string& input);
    void writeLogCMD();
};