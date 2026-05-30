cmake_minimum_required(VERSION 3.20)

project(FinanceServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)
find_package(unofficial-mysql-connector-cpp CONFIG REQUIRED)
find_package(httplib CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

file(GLOB_RECURSE SERVER_SOURCES "src/*.cpp")

add_executable(FinanceServer ${SERVER_SOURCES})

target_include_directories(FinanceServer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/shared
)

target_link_libraries(FinanceServer PRIVATE
    spdlog::spdlog
    nlohmann_json::nlohmann_json
    jwt-cpp::jwt-cpp
    unofficial::mysql-connector-cpp::connector
    httplib::httplib
    OpenSSL::SSL
    OpenSSL::Crypto
)
