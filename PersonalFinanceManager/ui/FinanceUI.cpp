#include "FinanceUI.h"

#include <algorithm>
#include <iostream>
#include <limits>

namespace finance
{
FinanceUI::FinanceUI(FinanceService& service) : service_(service)
{
}

std::string FinanceUI::promptLine(std::string const& message) const
{
    std::cout << message;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

std::string FinanceUI::promptOptional(std::string const& message) const
{
    std::cout << message;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

double FinanceUI::promptAmount(std::string const& message) const
{
    while (true)
    {
        std::string input = promptLine(message);
        try
        {
            double amount = std::stod(input);
            FinanceService::validateAmount(amount);
            return amount;
        }
        catch (std::exception const&)
        {
            std::cout << "Invalid amount. Please enter a positive number.\n";
        }
    }
}

void FinanceUI::showExpenses(std::vector<Expense> const& expenses) const
{
    if (expenses.empty())
    {
        std::cout << "No expenses recorded.\n";
        return;
    }

    std::cout << "\nExpenses:\n";
    std::cout << "ID | Date | Category | Amount | Description\n";
    for (auto const& expense : expenses)
    {
        std::cout << expense.id << " | " << expense.date << " | " << expense.category << " | "
                  << expense.amount << " | ";
        std::cout << (expense.description.has_value() ? *expense.description : "-") << "\n";
    }
}

void FinanceUI::showIncome(std::vector<Income> const& incomes) const
{
    if (incomes.empty())
    {
        std::cout << "No income recorded.\n";
        return;
    }

    std::cout << "\nIncome:\n";
    std::cout << "ID | Date | Source | Amount | Description\n";
    for (auto const& income : incomes)
    {
        std::cout << income.id << " | " << income.date << " | " << income.source << " | "
                  << income.amount << " | ";
        std::cout << (income.description.has_value() ? *income.description : "-") << "\n";
    }
}

void FinanceUI::showBudgets(std::vector<Budget> const& budgets) const
{
    if (budgets.empty())
    {
        std::cout << "No budgets set.\n";
        return;
    }

    std::cout << "\nBudgets:\n";
    std::cout << "Category | Amount | Period\n";
    for (auto const& budget : budgets)
    {
        std::cout << budget.category << " | " << budget.amount << " | " << budget.period << "\n";
    }
}

void FinanceUI::showSummary(Summary const& summary) const
{
    std::cout << "\nSummary:\n";
    std::cout << "Total income: " << summary.totalIncome << "\n";
    std::cout << "Total expenses: " << summary.totalExpenses << "\n";
    std::cout << "Balance: " << summary.balance << "\n";
    std::cout << "Category spending:\n";
    if (summary.spendingByCategory.empty())
    {
        std::cout << "  No spending recorded.\n";
    }
    else
    {
        for (auto const& pair : summary.spendingByCategory)
        {
            std::cout << "  " << pair.first << ": " << pair.second << "\n";
        }
    }
    if (!summary.budgets.empty())
    {
        std::cout << "Budgets and status:\n";
        for (auto const& budget : summary.budgets)
        {
            double spent = 0.0;
            auto found = summary.spendingByCategory.find(budget.category);
            if (found != summary.spendingByCategory.end())
            {
                spent = found->second;
            }
            double remaining = budget.amount - spent;
            std::cout << "  " << budget.category << ": budget " << budget.amount << " per "
                      << budget.period << ", spent " << spent << ", ";
            if (remaining < 0)
            {
                std::cout << "overspent by " << -remaining << "\n";
            }
            else
            {
                std::cout << "remaining " << remaining << "\n";
            }
        }
    }
}

void FinanceUI::addExpenseFlow() const
{
    std::string date = promptLine("Enter expense date (YYYY-MM-DD): ");
    std::string category = promptLine("Enter expense category: ");
    double amount = promptAmount("Enter expense amount: ");
    std::string description = promptOptional("Enter description (optional): ");

    try
    {
        int id = service_.addExpense(date, category, amount, description);
        std::cout << "Expense added with ID " << id << ".\n";
    }
    catch (std::exception const& exception)
    {
        std::cout << exception.what() << "\n";
    }
}

void FinanceUI::addIncomeFlow() const
{
    std::string date = promptLine("Enter income date (YYYY-MM-DD): ");
    std::string source = promptLine("Enter income source: ");
    double amount = promptAmount("Enter income amount: ");
    std::string description = promptOptional("Enter description (optional): ");

    try
    {
        int id = service_.addIncome(date, source, amount, description);
        std::cout << "Income added with ID " << id << ".\n";
    }
    catch (std::exception const& exception)
    {
        std::cout << exception.what() << "\n";
    }
}

void FinanceUI::addBudgetFlow() const
{
    std::string category = promptLine("Enter budget category: ");
    double amount = promptAmount("Enter budget amount: ");
    std::string period = promptLine("Enter budget period (e.g. monthly): ");

    try
    {
        int id = service_.addBudget(category, amount, period);
        std::cout << "Budget set with ID " << id << ".\n";
    }
    catch (std::exception const& exception)
    {
        std::cout << exception.what() << "\n";
    }
}

void FinanceUI::filterExpensesFlow() const
{
    std::string category = promptOptional("Enter category to filter by (leave blank for none): ");
    std::string startDate =
        promptOptional("Enter start date to filter by (YYYY-MM-DD, leave blank for none): ");
    std::string endDate =
        promptOptional("Enter end date to filter by (YYYY-MM-DD, leave blank for none): ");
    try
    {
        showExpenses(service_.filterExpenses(category, startDate, endDate));
    }
    catch (std::exception const& exception)
    {
        std::cout << exception.what() << "\n";
    }
}

void FinanceUI::deleteExpenseFlow() const
{
    std::string idText = promptLine("Enter expense ID to delete: ");
    try
    {
        int expenseId = std::stoi(idText);
        if (service_.deleteExpense(expenseId))
        {
            std::cout << "Expense deleted successfully.\n";
        }
        else
        {
            std::cout << "Expense not found.\n";
        }
    }
    catch (std::exception const&)
    {
        std::cout << "Invalid ID format.\n";
    }
}

void FinanceUI::run()
{
    while (true)
    {
        std::cout << "\nPersonal Finance Manager:\n";
        std::cout << "1) Add Expense\n";
        std::cout << "2) View Expenses\n";
        std::cout << "3) Filter Expenses\n";
        std::cout << "4) Delete Expense\n";
        std::cout << "5) Add Income\n";
        std::cout << "6) View Income\n";
        std::cout << "7) Create Budget\n";
        std::cout << "8) View Budgets\n";
        std::cout << "9) View Summary\n";
        std::cout << "0) Exit\n";
        std::string choice = promptLine("Choose an option: ");

        if (choice == "1")
        {
            addExpenseFlow();
        }
        else if (choice == "2")
        {
            showExpenses(service_.listExpenses());
        }
        else if (choice == "3")
        {
            filterExpensesFlow();
        }
        else if (choice == "4")
        {
            deleteExpenseFlow();
        }
        else if (choice == "5")
        {
            addIncomeFlow();
        }
        else if (choice == "6")
        {
            showIncome(service_.listIncome());
        }
        else if (choice == "7")
        {
            addBudgetFlow();
        }
        else if (choice == "8")
        {
            showBudgets(service_.listBudgets());
        }
        else if (choice == "9")
        {
            showSummary(service_.getSummary());
        }
        else if (choice == "0")
        {
            break;
        }
        else
        {
            std::cout << "Unknown selection.\n";
        }
    }
}
}  // namespace finance
