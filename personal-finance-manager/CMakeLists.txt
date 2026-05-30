cmake_minimum_required(VERSION 3.20)

project(PersonalFinanceManager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(finance-server)
add_subdirectory(finance-client)
add_subdirectory(tests)
