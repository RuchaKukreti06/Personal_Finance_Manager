#ifndef INC_FINANCE_UI_H
#define INC_FINANCE_UI_H

#include <string>
#include <vector>

#include "../types/Entities.h"
#include "FinanceService.h"

namespace finance
{
class FinanceUI
{
   public:
    explicit FinanceUI(FinanceService& service);
    void run();

   private:
    FinanceService& service_;
    std::string promptLine(const std::string& message) const;
    std::string promptOptional(const std::string& message) const;
    double promptAmount(const std::string& message) const;
    void showExpenses(const std::vector<Expense>& expenses) const;
    void showIncome(const std::vector<Income>& incomes) const;
    void showBudgets(const std::vector<Budget>& budgets) const;
    void showSummary(const Summary& summary) const;
    void addExpenseFlow() const;
    void addIncomeFlow() const;
    void addBudgetFlow() const;
    void filterExpensesFlow() const;
    void deleteExpenseFlow() const;
};

}  // namespace finance

#endif  // INC_FINANCE_UI_H
