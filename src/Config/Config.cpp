#include "Config.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <print>

ConfigSpace::Config ConfigSpace::MustLoad(const std::string& pathToConfig) {
    const std::string op { "Func::MustLoad()" };
    using json = nlohmann::json;

    std::ifstream f(pathToConfig);

    if (!f.is_open()) {
        std::println("{}, Cannot open a Config file", op);
        exit(1);
    }

    json data = json::parse(f);
    return data.get<ConfigSpace::Config>();
}