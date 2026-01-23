#pragma once

#include <string>

class Logger{
private:
    std::string m_path{};
public:
    Logger(const std::string& path) 
        : m_path(path) {}

    void writeToFile();
};