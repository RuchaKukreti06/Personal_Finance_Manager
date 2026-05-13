#ifndef INTERFACE_REPOSITORY_INTERFACES_H
#define INTERFACE_REPOSITORY_INTERFACES_H

#include <optional>
#include <string>
#include <vector>

#include "../types/Entities.h"

namespace finance
{
class IExpenseRepository
{
   public:
    virtual ~IExpenseRepository() = default;

    virtual int add(const Expense& expense) const = 0;
    virtual std::vector<Expense> list() const = 0;
    virtual std::vector<Expense> filter(const std::string& category, const std::string& startDate,
                                        const std::string& endDate) const = 0;
    virtual bool remove(int expenseId) const = 0;
};

class IIncomeRepository
{
   public:
    virtual ~IIncomeRepository() = default;

    virtual int add(const Income& income) const = 0;
    virtual std::vector<Income> list() const = 0;
};

class IBudgetRepository
{
   public:
    virtual ~IBudgetRepository() = default;

    // Add or replace a budget for a category
    virtual int addOrReplace(const Budget& budget) const = 0;

    virtual std::vector<Budget> list() const = 0;
    virtual std::optional<Budget> findByCategory(const std::string& category) const = 0;
};

class IUserRepository
{
   public:
    virtual ~IUserRepository() = default;

    virtual int add(const User& user) const = 0;
    virtual std::optional<User> findByUsername(const std::string& username) const = 0;
};

}  // namespace finance

#endif  // INTERFACE_REPOSITORY_INTERFACES_H
