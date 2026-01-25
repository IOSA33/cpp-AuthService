#include <iostream>
#include <sodium.h>
#include <string>
#include <cstring>
#include "../Storage.h"

bool Storage::createSessionID(const std::string& payload, int ttl) {
    const size_t BIN_SIZE { 32 };
    unsigned char hashed_session[BIN_SIZE];

    randombytes_buf(hashed_session, BIN_SIZE);

    const size_t HEX_SIZE = (BIN_SIZE * 2) + 1;
    std::vector<char> hex(HEX_SIZE);

    sodium_bin2hex(hex.data(), hex.size(), hashed_session, BIN_SIZE);

    // This is sending tcp request for my own implementation of Redis
    m_client.sendData("SET " + std::string(hex.data()) + " " + payload + " " + std::to_string(ttl));

    return true;
}

// Checks session in my own implementation of Redis
std::string Storage::getDataSessionID(const std::string& sessionID) {
    std::string result { m_client.getData("GET " + sessionID) };

    if (!result.empty()) {
        return result;
    }

    return "";
}

bool Storage::revokeSessionID(const std::string& sessionID) {
    std::string result { m_client.getData("DEL " + sessionID) };

    if (!result.empty()) {
        return false;
    }

    return true;
}

bool Storage::revokeAllSessionID(const std::string& email) {
    std::string result { m_client.getData("DELT " + email) };

    if (!result.empty()) {
        return false;
    }

    return true;
}

bool Storage::refreshSessionID(const std::string& sessionID, int ttl) {
    std::string result { m_client.getData("SET " + sessionID + " " + std::to_string(ttl)) };

    if (!result.empty()) {
        return false;
    }

    return true;
}