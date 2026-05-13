#pragma once

#include <optional>
#include <string>
#include <vector>

#include "../model/Entities.h"

namespace finance
{
class IExpenseRepository
{
   public:
    virtual ~IExpenseRepository() = default;
    virtual int add(Expense const& expense) const = 0;
    virtual std::vector<Expense> list() const = 0;
    virtual std::vector<Expense> filter(std::string const& category, std::string const& startDate,
                                        std::string const& endDate) const = 0;
    virtual bool remove(int expenseId) const = 0;
};

class IIncomeRepository
{
   public:
    virtual ~IIncomeRepository() = default;
    virtual int add(Income const& income) const = 0;
    virtual std::vector<Income> list() const = 0;
};

class IBudgetRepository
{
   public:
    virtual ~IBudgetRepository() = default;
    virtual int addOrReplace(Budget const& budget) const = 0;
    virtual std::vector<Budget> list() const = 0;
    virtual std::optional<Budget> findByCategory(std::string const& category) const = 0;
};

class IUserRepository
{
   public:
    virtual ~IUserRepository() = default;
    virtual int add(User const& user) const = 0;
    virtual std::optional<User> findByUsername(std::string const& username) const = 0;
};
}  // namespace finance
