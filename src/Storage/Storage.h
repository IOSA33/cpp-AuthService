#pragma once

#include <string>
#include <pqxx/pqxx>
#include "../Network/Client/Client.h"

class Storage{
private:
    std::string m_sql{};
    pqxx::connection m_C{};
    Client m_client;

public:
    Storage(const std::string& db_config, const int clientPort) 
    : m_C(db_config), m_client(clientPort) {
        connect();
        init();
    }

    void connect();
    void init();
    bool getUserInfo(const std::string& email);
    bool addUser(const std::string& email, const std::string& pass);
    bool checkEmail(const std::string& email);
    bool verifyUser(const std::string& email, const std::string& pass);
    bool deleteUser(const std::string& email, const std::string& pass);
    bool updateUserPass(const std::string& email, const std::string& oldPass, const std::string& newPass);
    
    bool createSessionID(const std::string& payload, int ttl);
    std::string getDataSessionID(const std::string& sessionID);
    bool revokeSessionID(const std::string& sessionID);
    bool revokeAllSessionID(const std::string& email);
    bool refreshSessionID(const std::string& sessionID, int ttl);
};