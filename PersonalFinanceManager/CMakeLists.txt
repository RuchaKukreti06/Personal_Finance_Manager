cmake_minimum_required(VERSION 3.15)
project(PersonalFinanceManagerCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find required packages
find_package(unofficial-sqlite3 CONFIG QUIET)
if (NOT unofficial-sqlite3_FOUND)
    find_package(SQLite3 REQUIRED)
endif()
find_package(OpenSSL REQUIRED)

# Determine SQLite target
set(SQLITE_LIB_TARGET "")
if (TARGET unofficial::sqlite3::sqlite3)
    set(SQLITE_LIB_TARGET unofficial::sqlite3::sqlite3)
elseif (TARGET SQLite::SQLite3)
    set(SQLITE_LIB_TARGET SQLite::SQLite3)
else()
    message(FATAL_ERROR "SQLite library target not found.")
endif()

# Main application executable
add_executable(finance-manager
    src/main.cpp
    src/Database.cpp
    src/PasswordHasher.cpp
    src/SQLiteRepositories.cpp
    src/FinanceService.cpp
    src/FinanceUI.cpp
)

target_include_directories(finance-manager 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/interface
        ${CMAKE_SOURCE_DIR}/types
        ${CMAKE_SOURCE_DIR}/constant
)

target_link_libraries(finance-manager PRIVATE ${SQLITE_LIB_TARGET} OpenSSL::Crypto)

# Test executable
add_executable(finance-manager-tests
    tests/TestDatabaseSchema.cpp
    tests/TestRepositoryInterfaces.cpp
    src/Database.cpp
    src/SQLiteRepositories.cpp
    src/PasswordHasher.cpp
    src/FinanceService.cpp
)

target_include_directories(finance-manager-tests 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/inc
        ${CMAKE_SOURCE_DIR}/interface
        ${CMAKE_SOURCE_DIR}/types
        ${CMAKE_SOURCE_DIR}/constant
)

target_link_libraries(finance-manager-tests PRIVATE ${SQLITE_LIB_TARGET} OpenSSL::Crypto)
