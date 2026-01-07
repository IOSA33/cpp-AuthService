#include <iostream>
#include <sodium.h>
#include <string>
#include <cstring>
#include "../Storage.h"

std::string Storage::createSessionID() {
    const size_t BIN_SIZE { 32 };
    unsigned char hashed_session[BIN_SIZE];

    randombytes_buf(hashed_session, BIN_SIZE);

    const size_t HEX_SIZE = (BIN_SIZE * 2) + 1;
    std::vector<char> hex(HEX_SIZE);

    sodium_bin2hex(hex.data(), hex.size(), hashed_session, BIN_SIZE);

    return std::string(hex.data());
}