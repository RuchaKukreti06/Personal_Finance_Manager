#ifndef INC_DATABASE_H
#define INC_DATABASE_H

#include <sqlite3.h>

#include <string>

namespace finance
{
class Database
{
   public:
    explicit Database(const std::string& path);
    ~Database();
    void initSchema() const;
    sqlite3* connection() const;

   private:
    void executeSql(const std::string& sql) const;

    sqlite3* db_ = nullptr;
    std::string path_;
};

}  // namespace finance

#endif  // INC_DATABASE_H
