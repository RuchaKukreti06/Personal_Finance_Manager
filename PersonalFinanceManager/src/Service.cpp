#include "Service.h"

#include <cctype>
#include <iomanip>
#include <regex>
#include <sstream>
#include <stdexcept>

FinanceService::FinanceService(ExpenseRepository& expenseRepo, IncomeRepository& incomeRepo, BudgetRepository& budgetRepo)
    : expenseRepo_(expenseRepo)
    , incomeRepo_(incomeRepo)
    , budgetRepo_(budgetRepo)
{
}

void FinanceService::validateAmount(double amount)
{
    if (amount <= 0.0)
    {
        throw std::invalid_argument("Amount must be greater than zero.");
    }
}

void FinanceService::validateText(std::string const& value, std::string const& fieldName)
{
    if (value.empty())
    {
        throw std::invalid_argument(fieldName + " cannot be empty.");
    }
}

void FinanceService::validateDate(std::string const& date)
{
    std::regex pattern(R"((\d{4})-(\d{2})-(\d{2}))");
    std::smatch match;
    if (!std::regex_match(date, match, pattern))
    {
        throw std::invalid_argument("Date must be in YYYY-MM-DD format.");
    }

    int year = std::stoi(match[1]);
    int month = std::stoi(match[2]);
    int day = std::stoi(match[3]);
    if (month < 1 || month > 12)
    {
        throw std::invalid_argument("Month must be between 01 and 12.");
    }
    if (day < 1 || day > 31)
    {
        throw std::invalid_argument("Day must be between 01 and 31.");
    }
}

int FinanceService::addExpense(std::string const& date, std::string const& category, double amount, std::string const& description) const
{
    validateDate(date);
    validateText(category, "Category");
    validateAmount(amount);

    Expense expense;
    expense.date = date;
    expense.category = category;
    expense.amount = amount;
    if (!description.empty())
    {
        expense.description = description;
    }

    return expenseRepo_.add(expense);
}

int FinanceService::addIncome(std::string const& date, std::string const& source, double amount, std::string const& description) const
{
    validateDate(date);
    validateText(source, "Source");
    validateAmount(amount);

    Income income;
    income.date = date;
    income.source = source;
    income.amount = amount;
    if (!description.empty())
    {
        income.description = description;
    }

    return incomeRepo_.add(income);
}

int FinanceService::addBudget(std::string const& category, double amount, std::string const& period) const
{
    validateText(category, "Category");
    validateText(period, "Period");
    validateAmount(amount);

    Budget budget;
    budget.category = category;
    budget.amount = amount;
    budget.period = period;
    return budgetRepo_.addOrReplace(budget);
}

bool FinanceService::deleteExpense(int expenseId) const
{
    if (expenseId <= 0)
    {
        throw std::invalid_argument("Expense ID must be a positive number.");
    }
    return expenseRepo_.remove(expenseId);
}

std::vector<Expense> FinanceService::listExpenses() const
{
    return expenseRepo_.list();
}

std::vector<Expense> FinanceService::filterExpenses(std::string const& category, std::string const& startDate, std::string const& endDate) const
{
    if (!startDate.empty())
    {
        validateDate(startDate);
    }
    if (!endDate.empty())
    {
        validateDate(endDate);
    }
    return expenseRepo_.filter(category, startDate, endDate);
}

std::vector<Income> FinanceService::listIncome() const
{
    return incomeRepo_.list();
}

std::vector<Budget> FinanceService::listBudgets() const
{
    return budgetRepo_.list();
}

Summary FinanceService::getSummary() const
{
    Summary summary;
    auto expenses = expenseRepo_.list();
    auto incomes = incomeRepo_.list();
    summary.budgets = budgetRepo_.list();

    for (auto const& expense : expenses)
    {
        summary.totalExpenses += expense.amount;
        summary.spendingByCategory[expense.category] += expense.amount;
    }

    for (auto const& income : incomes)
    {
        summary.totalIncome += income.amount;
    }

    summary.balance = summary.totalIncome - summary.totalExpenses;
    return summary;
}
