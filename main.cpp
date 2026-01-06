#include <iostream>
#include "src/AuthService.h"
#include "src/Logger/Logger.h"
#include "src/lib/RandomString.h"
#include <sodium.h>

int main() {
    if(sodium_init() < 0) {
        std::cout << "cannot use sodium!" << '\n';
        return 1;
    }
    
    // TODO: Init config
    Logger log{};

    // TODO: Configurate application from config file
    AuthService app{&log};
    app.run();
    
    return EXIT_SUCCESS;
}