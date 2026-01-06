#pragma once

#include <string>

struct RandomString {
    std::string m_random_string{};
    const std::string m_allChars {  "qwertyuiopasdfghjklzxcvbnm"
                                    "QWERTYUIOPASDFGHJKLZXCVBNM" 
                                    "0123456789"
                                    "+-.,/!%&()=[]{}@" };

    void generateRandom(const int length);
};