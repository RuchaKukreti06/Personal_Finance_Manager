#include "../inc/Database.h"

#include "../constant/Schema.h"
#include <stdexcept>

namespace finance
{
Database::Database(const std::string& path)
    : path_(path)
{
    int result = sqlite3_open(path_.c_str(), &db_);
    if (result != SQLITE_OK)
    {
        std::string errorMsg = sqlite3_errmsg(db_);
        throw std::runtime_error("Failed to open database: " + errorMsg);
    }
}

Database::~Database()
{
    if (db_)
    {
        sqlite3_close(db_);
        db_ = nullptr;
    }
}

void Database::executeSql(const std::string& sql) const
{
    if (!db_)
    {
        throw std::runtime_error("Database connection is not initialized.");
    }

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
    executeSql(DATABASE_SCHEMA);
}

sqlite3* Database::connection() const
{
    return db_;
}

} // namespace finance

