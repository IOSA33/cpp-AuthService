#include <iostream>
#include <sodium.h>
#include <string>
#include <cstring>
#include "../Storage.h"

bool Storage::createSessionID(const std::string& payload) {
    const size_t BIN_SIZE { 32 };
    unsigned char hashed_session[BIN_SIZE];

    randombytes_buf(hashed_session, BIN_SIZE);

    const size_t HEX_SIZE = (BIN_SIZE * 2) + 1;
    std::vector<char> hex(HEX_SIZE);

    sodium_bin2hex(hex.data(), hex.size(), hashed_session, BIN_SIZE);

    m_client.sendData("SET " + std::string(hex.data()) + " " + payload);

    return true;
}

// Checks session in my own Redis
std::string Storage::getDataSessionID(const std::string& sessionID) {
    std::string result { m_client.getData("GET " + sessionID) };

    if (!result.empty()) {
        return result;
    }

    return "No Value!";
}

bool Storage::revokeSessionID(const std::string& sessionID) {
    std::string result { m_client.getData("DELETE " + sessionID) };

    if (!result.empty()) {
        return false;
    }

    return true;
}
