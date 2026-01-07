#include <iostream>
#include <sodium.h>
#include <string>
#include <cstring>
#include "../Storage.h"
#include "../../lib/RandomString.h"

std::string Storage::createSessionID() {
    std::string randomStringToHash{ m_ranStrSession.generateRandom(5) };

    char hashed_session[crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str(hashed_session, randomStringToHash.c_str(), strlen(randomStringToHash.c_str()), crypto_pwhash_OPSLIMIT_SENSITIVE, crypto_pwhash_MEMLIMIT_SENSITIVE) != 0) {
        std::cout << "Cannot hash password: Out of memory!\n";
        return "";
    }

    std::string session(hashed_session);
    return session;
}