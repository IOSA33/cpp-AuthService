#include <iostream>
#include "src/AuthService.h"
#include "src/Logger/Logger.h"
#include "src/lib/RandomString.h"
#include <sodium.h>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    if (sodium_init() < 0) {
        std::cout << "cannot use sodium! Hashing is unsafe!" << '\n';
        return 1;
    }

    Logger log{};
    
    AuthService app{&log};
    app.run();
    
    return 0;
}