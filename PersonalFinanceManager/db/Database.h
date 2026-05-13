#pragma once

#include <sqlite3.h>

#include <string>

namespace finance
{
class Database
{
   public:
    explicit Database(std::string const& path);
    ~Database();

    void initSchema() const;
    sqlite3* connection() const;

   private:
    void executeSql(std::string const& sql) const;

    sqlite3* db_ = nullptr;
    std::string path_;
};
}  // namespace finance
