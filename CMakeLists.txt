cmake_minimum_required(VERSION 3.10)
project(authService VERSION 0.1)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Unit Tests
find_package(libpqxx REQUIRED)
find_package(GTest REQUIRED)
add_executable(unit_tests Tests/AuthService_unittest.cc
                          src/AuthService.cpp
                          src/Storage/Storage.cpp
                          src/Network/Client/Client.cpp
                          src/Storage/SessionID/SessionID.cpp
                          src/Logger/Logger.cpp)
target_link_libraries(unit_tests PRIVATE GTest::GTest stdc++exp libpqxx::pqxx sodium)

# Main app
find_package(libpqxx REQUIRED)
add_executable(app main.cpp
                   src/AuthService.cpp
                   src/Storage/Storage.cpp
                   src/Network/Client/Client.cpp
                   src/Storage/SessionID/SessionID.cpp
                   src/Logger/Logger.cpp)

target_link_libraries(app PRIVATE libpqxx::pqxx)
target_link_libraries(app PRIVATE sodium)
target_link_libraries(app PRIVATE stdc++exp)