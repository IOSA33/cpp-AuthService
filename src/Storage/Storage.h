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
    bool getUserInfo(const std::string& email);
    bool addUser(const std::string& email, const std::string& pass);
    bool checkEmail(const std::string& email);
    bool verifyUser(const std::string& email, const std::string& pass);
    bool deleteUser(const std::string& email);
    bool updateUserPass(const std::string& email, const std::string& pass);
    
    std::string createSessionID();
    bool verifySessionID(const std::string& sessionID);
    bool revokeSessionID(const std::string& sessionID);
    bool refreshSessionID(const std::string& sessionID);
};