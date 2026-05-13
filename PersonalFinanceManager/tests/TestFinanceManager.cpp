#include "Database.h"
#include "Repository.h"
#include "Service.h"

#include <cassert>
#include <filesystem>
#include <functional>
#include <iostream>

static void runTest(char const* name, std::function<void()> test)
{
    try
    {
        test();
        std::cout << name << " passed.\n";
    }
    catch (std::exception const& exception)
    {
        std::cerr << name << " failed: " << exception.what() << "\n";
        std::exit(EXIT_FAILURE);
    }
}

int main()
{
    auto path = std::filesystem::temp_directory_path() / "finance_manager_test.db";
    std::filesystem::remove(path);

    Database database(path.string());
    database.executeSchema();
    ExpenseRepository expenseRepo(database);
    IncomeRepository incomeRepo(database);
    BudgetRepository budgetRepo(database);
    FinanceService service(expenseRepo, incomeRepo, budgetRepo);

    runTest("Add and list expense", [&]() {
        int id = service.addExpense("2026-05-01", "Groceries", 42.5, "Dinner items");
        assert(id > 0);
        auto expenses = service.listExpenses();
        assert(expenses.size() == 1);
        assert(expenses[0].category == "Groceries");
    });

    runTest("Invalid expense amount", [&]() {
        try
        {
            service.addExpense("2026-05-01", "Books", 0.0, "Invalid");
            assert(false);
        }
        catch (std::invalid_argument const&)
        {
        }
    });

    runTest("Add income and summary", [&]() {
        service.addIncome("2026-05-02", "Salary", 1200.0, "May salary");
        auto summary = service.getSummary();
        assert(summary.totalIncome == 1200.0);
        assert(summary.totalExpenses == 42.5);
    });

    runTest("Set budget and retrieve", [&]() {
        int id = service.addBudget("Entertainment", 150.0, "monthly");
        assert(id > 0);
        auto budgets = service.listBudgets();
        assert(budgets.size() == 1);
        assert(budgets[0].category == "Entertainment");
    });

    runTest("Budget summary status", [&]() {
        service.addExpense("2026-05-04", "Entertainment", 100.0, "Movie");
        auto summary = service.getSummary();
        assert(summary.budgets.size() == 1);
        assert(summary.spendingByCategory.at("Entertainment") == 100.0);
    });

    runTest("Filter expenses by category", [&]() {
        auto filtered = service.filterExpenses("Groceries", "", "");
        assert(filtered.size() == 1);
    });

    runTest("Filter expenses by date range", [&]() {
        service.addExpense("2026-05-03", "Groceries", 20.0, "Milk");
        auto filtered = service.filterExpenses("", "2026-05-01", "2026-05-02");
        assert(filtered.size() == 1);
        assert(filtered[0].date == "2026-05-01");
    });

    runTest("Delete expense", [&]() {
        auto expenses = service.listExpenses();
        assert(!expenses.empty());
        bool removed = service.deleteExpense(expenses[0].id);
        assert(removed);
    });

    std::cout << "All tests passed.\n";
    return EXIT_SUCCESS;
}
