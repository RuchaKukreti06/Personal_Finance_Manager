#pragma once

#include <sqlite3.h>
#include <string>

class Database
{
public:
    explicit Database(std::string const& path);
    ~Database();

    void executeSchema() const;
    sqlite3* connection() const;

private:
    sqlite3* db_ = nullptr;
    std::string path_;

    void executeSql(std::string const& sql) const;
};
