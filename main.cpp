#include <iostream>
#include "src/AuthService.h"
#include "src/Logger/Logger.h"
#include <sodium.h>
#include <windows.h>

int main() {
    // For correct language output in console
    SetConsoleOutputCP(CP_UTF8);

    if (sodium_init() < 0) {
        std::cout << "Cannot use sodium! Hashing is unsafe!" << '\n';
        return 1;
    }

    // Initializing Logger
    Logger log{ "Config/config.json" };
    // Initializing App
    AuthService app{ &log };
    // Starting App
    app.run();
    
    return 0;
}