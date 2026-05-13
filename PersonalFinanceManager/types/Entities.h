#ifndef TYPES_ENTITIES_H
#define TYPES_ENTITIES_H

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace finance
{
// Domain model for expense records
struct Expense
{
    int id = -1;
    std::string date;
    std::string category;
    double amount = 0.0;
    std::optional<std::string> description;
};

// Domain model for income records
struct Income
{
    int id = -1;
    std::string date;
    std::string source;
    double amount = 0.0;
    std::optional<std::string> description;
};

// Domain model for budget constraints
struct Budget
{
    int id = -1;
    std::string category;
    double amount = 0.0;
    std::string period;
};

// Domain model for financial summary
struct Summary
{
    double totalIncome = 0.0;
    double totalExpenses = 0.0;
    double balance = 0.0;
    std::map<std::string, double> spendingByCategory;
    std::vector<Budget> budgets;
};

// Domain model for user accounts
struct User
{
    int id = -1;
    std::string username;
    std::string passwordHash;
};

} // namespace finance

#endif // TYPES_ENTITIES_H
