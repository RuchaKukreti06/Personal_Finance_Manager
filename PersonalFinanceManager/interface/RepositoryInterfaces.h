#ifndef INTERFACE_REPOSITORY_INTERFACES_H
#define INTERFACE_REPOSITORY_INTERFACES_H

#include <optional>
#include <string>
#include <vector>

#include "../types/Entities.h"

namespace finance
{
// Abstract interface for expense data operations
class IExpenseRepository
{
public:
    virtual ~IExpenseRepository() = default;

    // Add a new expense record
    virtual int add(const Expense& expense) const = 0;

    // Retrieve all expense records
    virtual std::vector<Expense> list() const = 0;

    // Filter expenses by category, start date, and end date
    virtual std::vector<Expense> filter(const std::string& category,
                                       const std::string& startDate,
                                       const std::string& endDate) const = 0;

    // Remove an expense by ID
    virtual bool remove(int expenseId) const = 0;
};

// Abstract interface for income data operations
class IIncomeRepository
{
public:
    virtual ~IIncomeRepository() = default;

    // Add a new income record
    virtual int add(const Income& income) const = 0;

    // Retrieve all income records
    virtual std::vector<Income> list() const = 0;
};

// Abstract interface for budget data operations
class IBudgetRepository
{
public:
    virtual ~IBudgetRepository() = default;

    // Add or replace a budget for a category
    virtual int addOrReplace(const Budget& budget) const = 0;

    // Retrieve all budgets
    virtual std::vector<Budget> list() const = 0;

    // Find a budget by category
    virtual std::optional<Budget> findByCategory(const std::string& category) const = 0;
};

// Abstract interface for user data operations
class IUserRepository
{
public:
    virtual ~IUserRepository() = default;

    // Add a new user
    virtual int add(const User& user) const = 0;

    // Find a user by username
    virtual std::optional<User> findByUsername(const std::string& username) const = 0;
};

} // namespace finance

#endif // INTERFACE_REPOSITORY_INTERFACES_H
