#include <cassert>
#include <cstdlib>
#include <functional>
#include <iostream>

#include "../inc/Database.h"
#include "../inc/PasswordHasher.h"
#include "../inc/SQLiteRepositories.h"

namespace finance
{
// Run a single test with error handling
void runTest(const char* testName, const std::function<void()>& testFunction)
{
    try
    {
        testFunction();
        std::cout << "✓ " << testName << " PASSED\n";
    }
    catch (const std::exception& ex)
    {
        std::cerr << "✗ " << testName << " FAILED: " << ex.what() << "\n";
        std::exit(EXIT_FAILURE);
    }
}

}  // namespace finance

int main()
{
    using namespace finance;

    std::cout << "\n=== Repository Interface Tests ===\n";

    Database database(":memory:");
    database.initSchema();

    SQLiteExpenseRepository expenseRepo(database);
    SQLiteIncomeRepository incomeRepo(database);
    SQLiteBudgetRepository budgetRepo(database);
    SQLiteUserRepository userRepo(database);

    runTest("Expense repository interface works with memory DB",
            [&]()
            {
                IExpenseRepository& repo = expenseRepo;
                Expense expense;
                expense.date = "2026-05-14";
                expense.category = "Travel";
                expense.amount = 99.95;
                expense.description = "Taxi";

                int id = repo.add(expense);
                assert(id > 0);
                auto list = repo.list();
                assert(list.size() == 1);
                assert(list[0].category == "Travel");
            });

    runTest("Income repository interface works with memory DB",
            [&]()
            {
                IIncomeRepository& repo = incomeRepo;
                Income income;
                income.date = "2026-05-14";
                income.source = "Freelance";
                income.amount = 500.0;
                income.description = "Project";

                int id = repo.add(income);
                assert(id > 0);
                auto list = repo.list();
                assert(list.size() == 1);
                assert(list[0].source == "Freelance");
            });

    runTest("Budget repository interface works with memory DB",
            [&]()
            {
                IBudgetRepository& repo = budgetRepo;
                Budget budget;
                budget.category = "Food";
                budget.amount = 300.0;
                budget.period = "monthly";

                int id = repo.addOrReplace(budget);
                assert(id > 0);
                auto found = repo.findByCategory("Food");
                assert(found.has_value());
                assert(found->amount == 300.0);
            });

    runTest("User repository interface works with memory DB",
            [&]()
            {
                IUserRepository& repo = userRepo;
                User user;
                user.username = "tester";
                user.passwordHash = PasswordHasher::hashPassword("secret");

                int id = repo.add(user);
                assert(id > 0);
                auto found = repo.findByUsername("tester");
                assert(found.has_value());
                assert(found->username == "tester");
                assert(PasswordHasher::verifyPassword("secret", found->passwordHash));
            });

    std::cout << "\nAll repository interface tests PASSED.\n\n";
    return EXIT_SUCCESS;
}
