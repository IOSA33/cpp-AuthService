#include <random>
#include <string>
#include "RandomString.h"

std::string RandomString::generateRandom(const int length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, m_allChars.size());   

    for (std::size_t i { 0 }; i < length; ++i) {
        m_random_string.push_back(m_allChars[static_cast<size_t>(dist(gen))]);
    }

    return m_random_string;
}