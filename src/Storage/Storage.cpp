#include "Storage.h"
#include <pqxx/pqxx>
#include <iostream>
#include <string>
#include <cstring>
#include <sodium.h>

void Storage::connect() {
    const std::string op { "Storage::connect" };
    try {
        if(m_C.is_open()) {
            std::cout << "DB opened successfully!" << " Name: " << m_C.dbname() << '\n';
        } else {
            std::cout << op << ", Can't open database" << std::endl;
            std::exit(1);
        }
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::exit(1);
    }
}

void Storage::init() {
    const std::string op { "Storage::init" };
    m_sql.clear();

    // Creating a new database if not already exists
    if (m_sql.empty()) {
        m_sql = "CREATE TABLE IF NOT EXISTS users("
                    "id         SERIAL PRIMARY KEY,"
                    "email      TEXT NOT NULL UNIQUE,"
                    "pass_hash  TEXT NOT NULL"
                ");"
                "CREATE INDEX IF NOT EXISTS idx_email ON users (email);";
    } else {
        std::cout << op << ", sql string is not a empty string!" << '\n';
        std::exit(1);
    }
   
    try {
        pqxx::work W(m_C); 
        pqxx::result result = W.exec(m_sql.c_str());
        W.commit();
        std::cout << "Table created successfully!" << '\n';

    } catch (const pqxx::sql_error &e) {
        std::cerr << op << ", SQL error: " << e.what() << '\n';
        std::exit(1);

    } catch (const std::exception &e) {
        std::cerr << op << ", Error in " << op << ", to init DB: " << e.what() << std::endl;
        std::exit(1);
    }
}

bool Storage::getUserInfo(const std::string& email) {
    const std::string op { "Storage::selectUser" };
    m_sql.clear();

    if (m_sql.empty()) {
        m_sql = "SELECT * FROM users WHERE email = ($1);"; 
    } else {
        std::cout << op << ", cmd is not a empty string!" << '\n';
        return false;
    }

    try {
        pqxx::nontransaction N(m_C);
        pqxx::result R( N.exec_params(m_sql.c_str(), email));
        if (R.empty()) {
            std::cout << op << ", No such email!\n";
            return false;
        }

        // Printing out result
        for(pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            std::cout << "ID: " << c[0].as<int>() << '\n';
            std::cout << "Email: " << c[1].as<std::string>() << '\n';
            std::cout << "Password: "<< c[2].as<std::string>() << '\n';
        }
        
        return true;
        
    } catch (const pqxx::sql_error &e) {
        std::cerr << op << ", SQL error: " << e.what() << '\n';
        return false;

    } catch (const std::exception &e) {
        std::cerr << op << ", General error: " << e.what() << std::endl;
        return false;
    }

    return false;
}

bool Storage::checkEmail(const std::string& email) {
    const std::string op { "Storage::checkEmail" }; 
    m_sql.clear();

    if (m_sql.empty()) {
        m_sql = "SELECT EXISTS(SELECT 1 FROM users WHERE email = ($1)) ";
    } else {
        std::cerr << op << ", sql string is no empty!" << '\n';
        return false;
    }

    // If true email exists, false email does not exists in db
    try {
        pqxx::nontransaction N(m_C);
        pqxx::result R( N.exec_params(m_sql.c_str(), email));
        bool exists { R[0][0].as<bool>() };
        if (!exists) {
            return false;
        }
        std::cout << "Email exists!" << '\n';
        return true;

    } catch (const pqxx::sql_error &e) {
        std::cerr << op << ", What: " << e.what() << '\n';
        return false;
    } catch (const std::exception &e) {
        std::cerr << op << ", General error: " << e.what() << '\n';
        return false;
    }

    return false;
}


bool Storage::addUser(const std::string& email, const std::string& pass) {
    const std::string op { "Storage::addUser" };
    m_sql.clear();
    // Because hashing is slow operation (1-2 sec) we should first check if user exists
    // If so we early return false from this function
    bool result { checkEmail(email) };
    if (result) {
        return false;
    }

    m_sql.clear();

    if (m_sql.empty()) {
        m_sql = "INSERT INTO users (email, pass_hash) VALUES ($1, $2);"; 
    } else {
        std::cout << op << ", cmd is not a empty string!" << '\n';
        return false;
    }

    char hashed_password[crypto_pwhash_STRBYTES];
    if (crypto_pwhash_str(hashed_password, pass.c_str(), strlen(pass.c_str()), crypto_pwhash_OPSLIMIT_SENSITIVE, crypto_pwhash_MEMLIMIT_SENSITIVE) != 0) {
        std::cout << "Cannot hash password: Out of memory!\n";
        return false;
    }

    try {
        pqxx::work W(m_C);
        pqxx::result result = W.exec_params(m_sql.c_str(), email, hashed_password);
        W.commit();
        if (result.affected_rows() > 0 ) {
            std::cout << "User added successfully!" << '\n';
            return true; 
        }
    } catch (const pqxx::sql_error &e) {
        std::cerr << op << ", What: " << e.what() << std::endl;
        return false;
    } catch (const std::exception &e) {
        std::cerr << op << ", General error: " << e.what() << std::endl;
        return false;
    }

    return false;
}

bool Storage::verifyUser(const std::string& email, const std::string& pass) {
    const std::string op { "Storage::verifyUser" };
    m_sql.clear();

    if (m_sql.empty()) {
        m_sql = "SELECT pass_hash FROM users WHERE email = ($1);"; 
    } else {
        std::cout << op << ", cmd is not a empty string!" << '\n';
        return false;
    }

    try {
        pqxx::nontransaction N(m_C);
        pqxx::result R( N.exec_params(m_sql.c_str(), email));
        if(R.empty()) {
            std::cout << op << ", No email found!\n";
            return false;
        }

        pqxx::result::const_iterator c = R.begin();
        if (crypto_pwhash_str_verify(c[0].as<std::string>().c_str(), pass.c_str(), strlen(pass.c_str())) != 0) {
            std::cout << "Password is Incorrect! Try again!" << '\n';
            return false;
        } else {
            std::cout << "Password is correct!" << '\n';
            return true;
        }

        return false;

    } catch (const pqxx::sql_error &e) {
        std::cerr << op << ", What: " << e.what() << '\n';
        return false;

    } catch (const std::exception &e) {
        std::cerr << op << ", General error: " << e.what() << '\n';
        return false;
    }

    return false;
}

// TODO: delteUser
bool Storage::deleteUser(const std::string& email) {
    const std::string op { "Storage::deleteUser" };
    
    
    return false;
}

bool Storage::updateUserPass(const std::string& email, const std::string& oldPass, const std::string& newPass) {
    const std::string op { "Storage::updateUserPass" };

    
    return false;
}