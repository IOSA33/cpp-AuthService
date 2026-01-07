#pragma once

#include <string>

struct RandomString {
    std::string m_random_string{};
    const std::string m_allChars {  "qwertyuiopasdfghjklzxcvbnm"
                                    "QWERTYUIOPASDFGHJKLZXCVBNM" 
                                    "0123456789"
                                    "+-.,/!%&()=[]{}@" };

    std::string generateRandom(const int length);
};