#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace ConfigSpace {
    struct AuthConfig {
        std::string jwt_secret{};
        int access_ttl{};
        int refresh_ttl{};
    };

    struct Config {
        std::string env{};
        int clientPort{};
        int serverPort{};
        AuthConfig auth{};
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AuthConfig, jwt_secret, access_ttl, refresh_ttl)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Config, env, clientPort, serverPort, auth)

    Config MustLoad(const std::string& pathToConfig);    
}
