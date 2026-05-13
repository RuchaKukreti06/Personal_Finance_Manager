#pragma once

#include <string>
#include <vector>

#include "../model/Entities.h"
#include "../repo/RepositoryInterfaces.h"

namespace finance
{
class FinanceService
{
   public:
    FinanceService(IExpenseRepository& expenseRepo, IIncomeRepository& incomeRepo,
                   IBudgetRepository& budgetRepo);

    int addExpense(std::string const& date, std::string const& category, double amount,
                   std::string const& description) const;
    int addIncome(std::string const& date, std::string const& source, double amount,
                  std::string const& description) const;
    int addBudget(std::string const& category, double amount, std::string const& period) const;
    bool deleteExpense(int expenseId) const;

    std::vector<Expense> listExpenses() const;
    std::vector<Expense> filterExpenses(std::string const& category, std::string const& startDate,
                                        std::string const& endDate) const;
    std::vector<Income> listIncome() const;
    std::vector<Budget> listBudgets() const;
    Summary getSummary() const;

    static void validateDate(std::string const& date);
    static void validateAmount(double amount);
    static void validateText(std::string const& value, std::string const& fieldName);

   private:
    IExpenseRepository& expenseRepo_;
    IIncomeRepository& incomeRepo_;
    IBudgetRepository& budgetRepo_;
};
}  // namespace finance
