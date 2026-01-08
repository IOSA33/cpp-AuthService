#pragma once

#include <string>

class Client {
private:
    int m_port{};

public:
    Client(int port) : m_port(port) {}

    std::string makeSocket(const std::string& data);
    bool sendData(const std::string& data);
    bool getData(const std::string& data);
};