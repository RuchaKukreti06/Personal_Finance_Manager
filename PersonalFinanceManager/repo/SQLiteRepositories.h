#pragma once

#include <string>
#include <vector>

#include "../db/Database.h"
#include "RepositoryInterfaces.h"

namespace finance
{
class SQLiteExpenseRepository : public IExpenseRepository
{
   public:
    explicit SQLiteExpenseRepository(Database& database);

    int add(Expense const& expense) const override;
    std::vector<Expense> list() const override;
    std::vector<Expense> filter(std::string const& category, std::string const& startDate,
                                std::string const& endDate) const override;
    bool remove(int expenseId) const override;

   private:
    Database& database_;
};

class SQLiteIncomeRepository : public IIncomeRepository
{
   public:
    explicit SQLiteIncomeRepository(Database& database);

    int add(Income const& income) const override;
    std::vector<Income> list() const override;

   private:
    Database& database_;
};

class SQLiteBudgetRepository : public IBudgetRepository
{
   public:
    explicit SQLiteBudgetRepository(Database& database);

    int addOrReplace(Budget const& budget) const override;
    std::vector<Budget> list() const override;
    std::optional<Budget> findByCategory(std::string const& category) const override;

   private:
    Database& database_;
};

class SQLiteUserRepository : public IUserRepository
{
   public:
    explicit SQLiteUserRepository(Database& database);

    int add(User const& user) const override;
    std::optional<User> findByUsername(std::string const& username) const override;

   private:
    Database& database_;
};
}  // namespace finance
