#ifndef INC_DATABASE_H
#define INC_DATABASE_H

#include <sqlite3.h>
#include <string>

namespace finance
{
// Manages SQLite database connection and schema initialization
class Database
{
public:
    // Initialize database with given file path
    explicit Database(const std::string& path);

    // Destructor closes database connection
    ~Database();

    // Create database schema if not exists
    void initSchema() const;

    // Get raw SQLite connection handle
    sqlite3* connection() const;

private:
    // Execute SQL statement
    void executeSql(const std::string& sql) const;

    sqlite3* db_ = nullptr;
    std::string path_;
};

} // namespace finance

#endif // INC_DATABASE_H
