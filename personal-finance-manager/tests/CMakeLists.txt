find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(GTest CONFIG REQUIRED)

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
    GTest::gtest_main
    spdlog::spdlog
    nlohmann_json::nlohmann_json
    jwt-cpp::jwt-cpp
    OpenSSL::SSL
    OpenSSL::Crypto
)

add_executable(test_date_utils
    server/test_date_utils.cpp
    ${CMAKE_SOURCE_DIR}/finance-server/src/utils/DateUtils.cpp
)

target_include_directories(test_date_utils PRIVATE
    ${CMAKE_SOURCE_DIR}/finance-server/include
    ${CMAKE_SOURCE_DIR}/shared
)

target_link_libraries(test_date_utils PRIVATE
    GTest::gtest_main
    nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(test_auth)
gtest_discover_tests(test_date_utils)
