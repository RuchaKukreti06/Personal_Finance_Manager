#include "../inc/Database.h"
#include "../inc/FinanceService.h"
#include "../inc/FinanceUI.h"
#include "../inc/SQLiteRepositories.h"

int main()
{
    finance::Database database("finance_manager.db");
    database.initSchema();

    finance::SQLiteExpenseRepository expenseRepo(database);
    finance::SQLiteIncomeRepository incomeRepo(database);
    finance::SQLiteBudgetRepository budgetRepo(database);
    finance::FinanceService service(expenseRepo, incomeRepo, budgetRepo);
    finance::FinanceUI ui(service);

    ui.run();
    return 0;
}
