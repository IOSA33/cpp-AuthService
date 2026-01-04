#include "Storage.h"
#include <pqxx/pqxx>
#include <iostream>
#include <string>

void Storage::connect() {
    try {
        pqxx::connection C("dbname = postgres user = postgres password = 1234 \
             hostaddr = 127.0.0.1 port = 5432");

        if(C.is_open()) {
            std::cout << "DB opened successfully!" << '\n';
        } else {
            std::cout << "Can't open database" << std::endl;
            return;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }   
}

void Storage::request(const std::string& input) {
    std::cout << "Called test" << '\n';
}