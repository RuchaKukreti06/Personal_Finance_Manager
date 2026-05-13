#pragma once

#include <string>
#include <vector>

#include "Models.h"
#include "Repository.h"

class FinanceService
{
public:
    FinanceService(ExpenseRepository& expenseRepo, IncomeRepository& incomeRepo, BudgetRepository& budgetRepo);

    int addExpense(std::string const& date, std::string const& category, double amount, std::string const& description) const;
    int addIncome(std::string const& date, std::string const& source, double amount, std::string const& description) const;
    int addBudget(std::string const& category, double amount, std::string const& period) const;
    bool deleteExpense(int expenseId) const;

    std::vector<Expense> listExpenses() const;
    std::vector<Expense> filterExpenses(std::string const& category, std::string const& startDate, std::string const& endDate) const;
    std::vector<Income> listIncome() const;
    std::vector<Budget> listBudgets() const;
    Summary getSummary() const;

    static void validateDate(std::string const& date);
    static void validateAmount(double amount);
    static void validateText(std::string const& value, std::string const& fieldName);

private:
    ExpenseRepository& expenseRepo_;
    IncomeRepository& incomeRepo_;
    BudgetRepository& budgetRepo_;
};
