#include <iostream>
#include <sodium.h>
#include <windows.h>
#include <chrono>
#include <print>
#include <format>
#include "src/AuthService.h"
#include "src/Logger/Logger.h"
#include "src/Config/Config.h"

void printCurrectTime();

int main() {
    // For correct language output in console
    SetConsoleOutputCP(CP_UTF8);

    if (sodium_init() < 0) {
        std::cout << "Cannot use sodium! Hashing is unsafe!" << '\n';
        return 1;
    }

    printCurrectTime();

    // Initializing Config
    ConfigSpace::Config cfg { ConfigSpace::MustLoad("../Config/config.json") };
    // Initializing Logger
    Logger log{ "LogForCMDs.txt" };
    // Initializing App
    AuthService app{ &log };
    // Starting App
    app.run();
    
    return 0;
}

void printCurrectTime() {
    const auto now = std::chrono::system_clock::now();
    auto zt_local = std::chrono::zoned_time{ std::chrono::current_zone(), now };
    std::print("now is {}\n", zt_local);
}
