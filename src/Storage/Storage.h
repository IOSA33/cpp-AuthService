#pragma once

#include <string>

class Storage{
private:


public:
    Storage() {
        connect();
    } 

    void connect();
    void request(const std::string& input);
};