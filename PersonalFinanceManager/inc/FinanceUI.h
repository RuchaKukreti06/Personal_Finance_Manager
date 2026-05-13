#ifndef INC_FINANCE_UI_H
#define INC_FINANCE_UI_H

#include <string>
#include <vector>

#include "FinanceService.h"
#include "../types/Entities.h"

namespace finance
{
// User interface layer for console interactions
class FinanceUI
{
public:
    explicit FinanceUI(FinanceService& service);

    // Run the interactive UI loop
    void run();

private:
    FinanceService& service_;

    // Input prompts
    std::string promptLine(const std::string& message) const;
    std::string promptOptional(const std::string& message) const;
    double promptAmount(const std::string& message) const;

    // Display methods
    void showExpenses(const std::vector<Expense>& expenses) const;
    void showIncome(const std::vector<Income>& incomes) const;
    void showBudgets(const std::vector<Budget>& budgets) const;
    void showSummary(const Summary& summary) const;

    // Workflow handlers
    void addExpenseFlow() const;
    void addIncomeFlow() const;
    void addBudgetFlow() const;
    void filterExpensesFlow() const;
    void deleteExpenseFlow() const;
};

} // namespace finance

#endif // INC_FINANCE_UI_H
