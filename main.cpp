#include <iostream>
#include "src/AuthService.h"
#include "src/Logger/Logger.h"

int main() {
    // TODO: Init config

    Logger log{};

    // TODO: Configurate application from config file
    AuthService app{&log};
    app.run();

    // TODO: Run Application

    return EXIT_SUCCESS;
}