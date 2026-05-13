#include <sqlite3.h>

#include <cassert>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

#include "../inc/Database.h"

namespace finance
{
// Check if a table exists in the database
bool tableExists(sqlite3* db, const std::string& tableName)
{
    const char* sql = "SELECT name FROM sqlite_master WHERE type='table' AND name=?;";
    sqlite3_stmt* statement = nullptr;

    int result = sqlite3_prepare_v2(db, sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_text(statement, 1, tableName.c_str(), -1, SQLITE_TRANSIENT);
    result = sqlite3_step(statement);
    bool exists = (result == SQLITE_ROW);

    sqlite3_finalize(statement);
    return exists;
}

// Run a single test with error handling
void runTest(const char* testName, const std::function<void()>& testFunction)
{
    try
    {
        testFunction();
        std::cout << "✓ " << testName << " PASSED\n";
    }
    catch (const std::exception& ex)
    {
        std::cerr << "✗ " << testName << " FAILED: " << ex.what() << "\n";
        std::exit(EXIT_FAILURE);
    }
}

}  // namespace finance

int main()
{
    using namespace finance;

    std::cout << "\n=== Database Schema Tests ===\n";

    Database database(":memory:");
    database.initSchema();

    runTest("Schema creates expenses table",
            [&]() { assert(tableExists(database.connection(), "expenses")); });

    runTest("Schema creates income table",
            [&]() { assert(tableExists(database.connection(), "income")); });

    runTest("Schema creates budgets table",
            [&]() { assert(tableExists(database.connection(), "budgets")); });

    runTest("Schema creates users table",
            [&]() { assert(tableExists(database.connection(), "users")); });

    std::cout << "\nAll database schema tests PASSED.\n\n";
    return EXIT_SUCCESS;
}
