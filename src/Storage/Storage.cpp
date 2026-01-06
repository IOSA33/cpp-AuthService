#include "Storage.h"
#include <pqxx/pqxx>
#include <iostream>
#include <string>
#include <sodium.h>

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
    
    if (m_sql.empty()) {
        m_sql = "SELECT * FROM users WHERE email = ($1);"; 
    } else {
        std::cout << op << ", cmd is not a empty string!" << '\n';
        return;
    }

    pqxx::nontransaction N(m_C);
    pqxx::result R( N.exec_params(m_sql.c_str(), email));

    // Printing out result
    for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
        std::cout << "ID: " << c[0].as<int>() << '\n';
        std::cout << "Email: " << c[1].as<std::string>() << '\n';
        std::cout << "Password: "<< c[2].as<std::string>() << '\n';
    }

    std::cout << "selectUser Completed!" << '\n';
}

void Storage::addUser(const std::string& email, const std::string& pass) {
    const std::string op { "Storage::addUser" };

    char hashed_password[crypto_pwhash_STRBYTES];
    if (crypto_pwhash_str(hashed_password, pass.c_str(), strlen(pass.c_str()), crypto_pwhash_OPSLIMIT_SENSITIVE, crypto_pwhash_MEMLIMIT_SENSITIVE) != 0) {
        std::cout << "Cannot hash password: Out of memory!\n";
        return;
    }

    if (m_sql.empty()) {
        m_sql = "INSERT INTO users (email, pass_hash) VALUES ($1, $2);"; 
    } else {
        std::cout << op << ", cmd is not a empty string!" << '\n';
        return;
    }

    pqxx::work W(m_C);

    // correct input should contain only utf-8 carracteres
    W.exec_params(m_sql.c_str(), email, hashed_password);
    W.commit();

    std::cout << "User added successfully!" << '\n';
    
    // Emptying sql command
    m_sql.clear();
}

void Storage::verifyUser(const std::string& email, const std::string& pass) {
    const std::string op { "Storage::verifyUser" };
    
    if (m_sql.empty()) {
        m_sql = "SELECT pass_hash FROM users WHERE email = ($1);"; 
    } else {
        std::cout << op << ", cmd is not a empty string!" << '\n';
        return;
    }

    pqxx::nontransaction N(m_C);
    pqxx::result R( N.exec_params(m_sql.c_str(), email));
    if(R.empty()) {
        std::cout << "No email found!\n";
        return;
    }

    pqxx::result::const_iterator c = R.begin();

    if (crypto_pwhash_str_verify(c[0].as<std::string>().c_str(), pass.c_str(), strlen(pass.c_str())) != 0) {
        std::cout << "Password is Incorrect! Try again!" << '\n';
        return;
    } else {
        std::cout << "Password is correct!" << '\n';
    }
}

void Storage::deleteUser(const std::string& email) {
    const std::string op { "Storage::deleteUser" };

    std::cout << "Called deleteUser test" << '\n';
}

void Storage::blackListUser(const std::string& email) {
    const std::string op { "Storage::blackListUser" };

    std::cout << "Called blackListUser test" << '\n';
}
