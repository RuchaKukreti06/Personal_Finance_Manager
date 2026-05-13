#ifndef INC_FINANCE_SERVICE_H
#define INC_FINANCE_SERVICE_H

#include <string>
#include <vector>

#include "../interface/RepositoryInterfaces.h"
#include "../types/Entities.h"

namespace finance
{
// Business logic layer for financial operations
class FinanceService
{
public:
    FinanceService(IExpenseRepository& expenseRepo,
                   IIncomeRepository& incomeRepo,
                   IBudgetRepository& budgetRepo);

    // Expense operations
    int addExpense(const std::string& date,
                   const std::string& category,
                   double amount,
                   const std::string& description) const;
    std::vector<Expense> listExpenses() const;
    std::vector<Expense> filterExpenses(const std::string& category,
                                       const std::string& startDate,
                                       const std::string& endDate) const;
    bool deleteExpense(int expenseId) const;

    // Income operations
    int addIncome(const std::string& date,
                  const std::string& source,
                  double amount,
                  const std::string& description) const;
    std::vector<Income> listIncome() const;

    // Budget operations
    int addBudget(const std::string& category,
                  double amount,
                  const std::string& period) const;
    std::vector<Budget> listBudgets() const;

    // Summary operations
    Summary getSummary() const;

    // Validation methods
    static void validateDate(const std::string& date);
    static void validateAmount(double amount);
    static void validateText(const std::string& value, const std::string& fieldName);

private:
    IExpenseRepository& expenseRepo_;
    IIncomeRepository& incomeRepo_;
    IBudgetRepository& budgetRepo_;
};

} // namespace finance

#endif // INC_FINANCE_SERVICE_H
