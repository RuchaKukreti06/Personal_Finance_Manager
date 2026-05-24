cmake_minimum_required(VERSION 3.20)

project(PersonalFinanceManager)

set(CMAKE_CXX_STANDARD 20)

find_package(ftxui CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)
find_package(unofficial-mysql-connector-cpp CONFIG REQUIRED)

add_executable(PersonalFinanceManager
    src/main.cpp
)

target_link_libraries(PersonalFinanceManager PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
    spdlog::spdlog
    nlohmann_json::nlohmann_json
    jwt-cpp::jwt-cpp
    unofficial::mysql-connector-cpp::connector
)