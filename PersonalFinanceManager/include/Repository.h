#pragma once

#include <string>
#include <vector>

#include "Database.h"
#include "Models.h"

class ExpenseRepository
{
public:
    explicit ExpenseRepository(Database& database);

    int add(Expense const& expense) const;
    std::vector<Expense> list() const;
    std::vector<Expense> filter(std::string const& category, std::string const& startDate, std::string const& endDate) const;
    bool remove(int expenseId) const;

private:
    Database& database_;
};

class IncomeRepository
{
public:
    explicit IncomeRepository(Database& database);

    int add(Income const& income) const;
    std::vector<Income> list() const;

private:
    Database& database_;
};

class BudgetRepository
{
public:
    explicit BudgetRepository(Database& database);

    int addOrReplace(Budget const& budget) const;
    std::vector<Budget> list() const;
    std::optional<Budget> findByCategory(std::string const& category) const;

private:
    Database& database_;
};
