#pragma once

#include <map>
#include <optional>
#include <string>
#include <vector>

struct Expense
{
    int id{-1};
    std::string date;
    std::string category;
    double amount{0.0};
    std::optional<std::string> description;
};

struct Income
{
    int id{-1};
    std::string date;
    std::string source;
    double amount{0.0};
    std::optional<std::string> description;
};

struct Budget
{
    int id{-1};
    std::string category;
    double amount{0.0};
    std::string period;
};

struct Summary
{
    double totalIncome{0.0};
    double totalExpenses{0.0};
    double balance{0.0};
    std::map<std::string, double> spendingByCategory;
    std::vector<Budget> budgets;
};
