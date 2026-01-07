#pragma once

#include <string>
#include <pqxx/pqxx>

class Storage{
private:
    std::string m_sql{};
    pqxx::connection m_C{};

public:
    explicit Storage(const std::string& db_config) : m_C(db_config) {
        connect();
        init();
    }

    void connect();
    void init();
    bool selectUser(const std::string& email);
    bool addUser(const std::string& email, const std::string& pass);
    bool verifyUser(const std::string& email, const std::string& pass);
    bool deleteUser(const std::string& email);
    bool blackListUser(const std::string& email);
};