#pragma once

#include "Storage/Storage.h"
#include <vector>

class Logger;

class AuthService{
private:
    // TODO: Connect DataBase;
    Storage m_storage{};

    // TODO: Logger
    Logger* m_logger{};
    // TODO: for future its needs to be a json format
    // Imagine client sends json file from website form
    std::vector<std::string> m_currentLine{};

public:
    // TODO: Constuctor
    AuthService(Logger* logger) 
        : m_logger(logger) {}
    
        // TODO: Destructor
    ~AuthService() {}

    // Run the app
    void run();
    
    // TODO: Graceful shotdown
    
};