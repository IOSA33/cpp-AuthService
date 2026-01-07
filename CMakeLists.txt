cmake_minimum_required(VERSION 3.10)
project(authService VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wno-cpp)

find_package(libpqxx REQUIRED)

add_executable(app main.cpp
                   src/AuthService.cpp
                   src/Storage/Storage.cpp
                   src/Network/Client/Client.cpp
                   src/Storage/SessionID/SessionID.cpp)

target_link_libraries(app PRIVATE libpqxx::pqxx)
target_link_libraries(app PRIVATE sodium)