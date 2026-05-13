#pragma once

#include <string>
#include <vector>

#include "../model/Entities.h"
#include "../service/FinanceService.h"

namespace finance
{
class FinanceUI
{
   public:
    explicit FinanceUI(FinanceService& service);
    void run();

   private:
    FinanceService& service_;

    std::string promptLine(std::string const& message) const;
    std::string promptOptional(std::string const& message) const;
    double promptAmount(std::string const& message) const;
    void showExpenses(std::vector<Expense> const& expenses) const;
    void showIncome(std::vector<Income> const& incomes) const;
    void showBudgets(std::vector<Budget> const& budgets) const;
    void showSummary(Summary const& summary) const;
    void addExpenseFlow() const;
    void addIncomeFlow() const;
    void addBudgetFlow() const;
    void filterExpensesFlow() const;
    void deleteExpenseFlow() const;
};
}  // namespace finance
