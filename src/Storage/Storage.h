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
    void selectUser(const std::string& email);
    void addUser(const std::string& email, const std::string& pass);
    void verifyUser(const std::string& email, const std::string& pass);
    void deleteUser(const std::string& email);
    void blackListUser(const std::string& email);
};