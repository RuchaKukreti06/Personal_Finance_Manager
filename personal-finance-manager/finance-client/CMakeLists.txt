cmake_minimum_required(VERSION 3.20)

project(FinanceClient)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ftxui CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB_RECURSE CLIENT_SOURCES "src/*.cpp")

add_executable(FinanceClient ${CLIENT_SOURCES})

target_include_directories(FinanceClient PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/shared
)

target_link_libraries(FinanceClient PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
    spdlog::spdlog
    nlohmann_json::nlohmann_json
)
