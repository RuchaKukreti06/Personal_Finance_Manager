cmake_minimum_required(VERSION 3.20)

project(FinanceServerTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(test_auth
    server/test_auth_service.cpp
    ${CMAKE_SOURCE_DIR}/finance-server/src/auth/PasswordHasher.cpp
    ${CMAKE_SOURCE_DIR}/finance-server/src/auth/JwtManager.cpp
)

target_include_directories(test_auth PRIVATE
    ${CMAKE_SOURCE_DIR}/finance-server/include
    ${CMAKE_SOURCE_DIR}/shared
)

target_link_libraries(test_auth PRIVATE
    spdlog::spdlog
    nlohmann_json::nlohmann_json
    jwt-cpp::jwt-cpp
    OpenSSL::SSL
    OpenSSL::Crypto
)

enable_testing()
add_test(NAME AuthTests COMMAND test_auth)
