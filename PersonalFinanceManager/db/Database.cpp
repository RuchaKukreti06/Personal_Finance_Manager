#include "Database.h"

#include <stdexcept>

namespace finance
{
namespace
{
const char* kSchema = R"(
CREATE TABLE IF NOT EXISTS expenses (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    date TEXT NOT NULL,
    category TEXT NOT NULL,
    amount REAL NOT NULL,
    description TEXT
);

CREATE TABLE IF NOT EXISTS income (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    date TEXT NOT NULL,
    source TEXT NOT NULL,
    amount REAL NOT NULL,
    description TEXT
);

CREATE TABLE IF NOT EXISTS budgets (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    category TEXT NOT NULL UNIQUE,
    amount REAL NOT NULL,
    period TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password_hash TEXT NOT NULL
);
)";
}  // namespace

Database::Database(std::string const& path) : path_(path)
{
    int result = sqlite3_open(path_.c_str(), &db_);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to open database: " + std::string(sqlite3_errmsg(db_)));
    }
}

Database::~Database()
{
    if (db_)
    {
        sqlite3_close(db_);
    }
}

void Database::executeSql(std::string const& sql) const
{
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK)
    {
        std::string error = errorMessage ? errorMessage : "Unknown SQLite error";
        sqlite3_free(errorMessage);
        throw std::runtime_error("SQLite execution error: " + error);
    }
}

void Database::initSchema() const
{
    executeSql(kSchema);
}

sqlite3* Database::connection() const
{
    return db_;
}
}  // namespace finance
