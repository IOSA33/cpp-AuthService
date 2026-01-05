#include "Storage.h"
#include <pqxx/pqxx>
#include <iostream>
#include <string>

void Storage::connect() {
    const std::string op { "Storage::connect" };
    try {
        if(m_C.is_open()) {
            std::cout << "DB opened successfully!" << "Name: " << m_C.dbname() << '\n';
        } else {
            std::cout << "Can't open database" << std::endl;
            std::exit(1);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::exit(1);
    }
}

void Storage::init() {
    const std::string op { "Storage::init" };

    // Creating a new database if not already exists
    if (m_sql.empty()) {
        m_sql = "CREATE TABLE IF NOT EXISTS users(" \
                    "id         SERIAL PRIMARY KEY," \
                    "email      TEXT NOT NULL UNIQUE," \
                    "pass_hash  TEXT NOT NULL" \
                ");" \
                "CREATE INDEX IF NOT EXISTS idx_email ON users (email);";
    } else {
        std::cout << "Error in Storage::init(), cmd is not a empty string!" << '\n';
        return;
    }
    pqxx::work W(m_C);
    
    W.exec(m_sql.c_str());
    W.commit();

    std::cout << "Table created successfully" << '\n';
    
    // Emptying sql command
    m_sql.clear();
}

void Storage::selectUser(const std::string& email) {
    const std::string op { "Storage::selectUser" };
    std::cout << "Called selectUser test" << '\n';
}

void Storage::addUser(const std::string& email, const std::string& pass) {
    const std::string op { "Storage::addUser" };

    if (m_sql.empty()) {
        m_sql = "INSERT INTO users (email, pass_hash) VALUES ('" + email + "', '" + pass + "');"; 
    } else {
        std::cout << op << ", cmd is not a empty string!" << '\n';
        return;
    }

    pqxx::work W(m_C);
    
    W.exec(m_sql.c_str());
    W.commit();

    std::cout << "User added successfully!" << '\n';
    
    // Emptying sql command
    m_sql.clear();
}

void Storage::deleteUser(const std::string& email) {
    const std::string op { "Storage::deleteUser" };

    std::cout << "Called deleteUser test" << '\n';
}

void Storage::blackListUser(const std::string& email) {
    const std::string op { "Storage::blackListUser" };

    std::cout << "Called blackListUser test" << '\n';
}
