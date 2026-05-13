#ifndef INC_SQLITE_REPOSITORIES_H
#define INC_SQLITE_REPOSITORIES_H

#include <optional>
#include <string>
#include <vector>

#include "../interface/RepositoryInterfaces.h"
#include "Database.h"

namespace finance
{
class SQLiteExpenseRepository : public IExpenseRepository
{
   public:
    explicit SQLiteExpenseRepository(Database& database);

    int add(const Expense& expense) const override;
    std::vector<Expense> list() const override;
    std::vector<Expense> filter(const std::string& category, const std::string& startDate,
                                const std::string& endDate) const override;
    bool remove(int expenseId) const override;

   private:
    Database& database_;
};

class SQLiteIncomeRepository : public IIncomeRepository
{
   public:
    explicit SQLiteIncomeRepository(Database& database);

    int add(const Income& income) const override;
    std::vector<Income> list() const override;

   private:
    Database& database_;
};

class SQLiteBudgetRepository : public IBudgetRepository
{
   public:
    explicit SQLiteBudgetRepository(Database& database);

    int addOrReplace(const Budget& budget) const override;
    std::vector<Budget> list() const override;
    std::optional<Budget> findByCategory(const std::string& category) const override;

   private:
    Database& database_;
};

class SQLiteUserRepository : public IUserRepository
{
   public:
    explicit SQLiteUserRepository(Database& database);

    int add(const User& user) const override;
    std::optional<User> findByUsername(const std::string& username) const override;

   private:
    Database& database_;
};

}  // namespace finance

#endif  // INC_SQLITE_REPOSITORIES_H
