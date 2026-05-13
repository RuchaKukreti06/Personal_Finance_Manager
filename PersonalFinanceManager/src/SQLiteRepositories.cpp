#include "../inc/SQLiteRepositories.h"

#include <stdexcept>

namespace finance
{
namespace
{
std::string columnText(sqlite3_stmt* statement, int index)
{
    const unsigned char* text = sqlite3_column_text(statement, index);
    return text ? reinterpret_cast<const char*>(text) : std::string();
}

int executeInsert(sqlite3_stmt* statement, Database& database)
{
    int result = sqlite3_step(statement);
    if (result != SQLITE_DONE)
    {
        sqlite3_finalize(statement);
        throw std::runtime_error("Failed to execute insert statement.");
    }
    return static_cast<int>(sqlite3_last_insert_rowid(database.connection()));
}

} // namespace

// ==================== SQLiteExpenseRepository ====================

SQLiteExpenseRepository::SQLiteExpenseRepository(Database& database)
    : database_(database)
{
}

int SQLiteExpenseRepository::add(const Expense& expense) const
{
    const char* sql = "INSERT INTO expenses (date, category, amount, description) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* statement = nullptr;

    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare expense insert statement.");
    }

    sqlite3_bind_text(statement, 1, expense.date.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, expense.category.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(statement, 3, expense.amount);

    if (expense.description.has_value())
    {
        sqlite3_bind_text(statement, 4, expense.description->c_str(), -1, SQLITE_TRANSIENT);
    }
    else
    {
        sqlite3_bind_null(statement, 4);
    }

    int id = executeInsert(statement, const_cast<Database&>(database_));
    sqlite3_finalize(statement);
    return id;
}

std::vector<Expense> SQLiteExpenseRepository::list() const
{
    const char* sql = "SELECT id, date, category, amount, description FROM expenses ORDER BY date DESC;";
    sqlite3_stmt* statement = nullptr;

    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare expense list query.");
    }

    std::vector<Expense> expenses;
    while ((result = sqlite3_step(statement)) == SQLITE_ROW)
    {
        Expense expense;
        expense.id = sqlite3_column_int(statement, 0);
        expense.date = columnText(statement, 1);
        expense.category = columnText(statement, 2);
        expense.amount = sqlite3_column_double(statement, 3);

        std::string description = columnText(statement, 4);
        if (!description.empty())
        {
            expense.description = description;
        }

        expenses.push_back(expense);
    }

    sqlite3_finalize(statement);
    return expenses;
}

std::vector<Expense> SQLiteExpenseRepository::filter(const std::string& category,
                                                    const std::string& startDate,
                                                    const std::string& endDate) const
{
    std::string sql = "SELECT id, date, category, amount, description FROM expenses";
    bool hasCategory = !category.empty();
    bool hasStartDate = !startDate.empty();
    bool hasEndDate = !endDate.empty();

    if (hasCategory || hasStartDate || hasEndDate)
    {
        sql += " WHERE ";
        bool firstClause = true;

        if (hasCategory)
        {
            sql += "category = ?";
            firstClause = false;
        }

        if (hasStartDate)
        {
            if (!firstClause)
                sql += " AND ";
            sql += "date >= ?";
            firstClause = false;
        }

        if (hasEndDate)
        {
            if (!firstClause)
                sql += " AND ";
            sql += "date <= ?";
        }
    }

    sql += " ORDER BY date DESC;";
    sqlite3_stmt* statement = nullptr;

    int result = sqlite3_prepare_v2(database_.connection(), sql.c_str(), -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare expense filter query.");
    }

    int bindIndex = 1;
    if (hasCategory)
    {
        sqlite3_bind_text(statement, bindIndex++, category.c_str(), -1, SQLITE_TRANSIENT);
    }
    if (hasStartDate)
    {
        sqlite3_bind_text(statement, bindIndex++, startDate.c_str(), -1, SQLITE_TRANSIENT);
    }
    if (hasEndDate)
    {
        sqlite3_bind_text(statement, bindIndex++, endDate.c_str(), -1, SQLITE_TRANSIENT);
    }

    std::vector<Expense> expenses;
    while ((result = sqlite3_step(statement)) == SQLITE_ROW)
    {
        Expense expense;
        expense.id = sqlite3_column_int(statement, 0);
        expense.date = columnText(statement, 1);
        expense.category = columnText(statement, 2);
        expense.amount = sqlite3_column_double(statement, 3);

        std::string description = columnText(statement, 4);
        if (!description.empty())
        {
            expense.description = description;
        }

        expenses.push_back(expense);
    }

    sqlite3_finalize(statement);
    return expenses;
}

bool SQLiteExpenseRepository::remove(int expenseId) const
{
    const char* sql = "DELETE FROM expenses WHERE id = ?;";
    sqlite3_stmt* statement = nullptr;

    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare expense delete query.");
    }

    sqlite3_bind_int(statement, 1, expenseId);
    result = sqlite3_step(statement);
    int rowCount = sqlite3_changes(database_.connection());

    sqlite3_finalize(statement);
    return rowCount > 0;
}

// ==================== SQLiteIncomeRepository ====================

SQLiteIncomeRepository::SQLiteIncomeRepository(Database& database)
    : database_(database)
{
}

int SQLiteIncomeRepository::add(const Income& income) const
{
    const char* sql = "INSERT INTO income (date, source, amount, description) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* statement = nullptr;

    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare income insert statement.");
    }

    sqlite3_bind_text(statement, 1, income.date.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, income.source.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(statement, 3, income.amount);

    if (income.description.has_value())
    {
        sqlite3_bind_text(statement, 4, income.description->c_str(), -1, SQLITE_TRANSIENT);
    }
    else
    {
        sqlite3_bind_null(statement, 4);
    }

    int id = executeInsert(statement, const_cast<Database&>(database_));
    sqlite3_finalize(statement);
    return id;
}

std::vector<Income> SQLiteIncomeRepository::list() const
{
    const char* sql = "SELECT id, date, source, amount, description FROM income ORDER BY date DESC;";
    sqlite3_stmt* statement = nullptr;

    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare income list query.");
    }

    std::vector<Income> incomes;
    while ((result = sqlite3_step(statement)) == SQLITE_ROW)
    {
        Income income;
        income.id = sqlite3_column_int(statement, 0);
        income.date = columnText(statement, 1);
        income.source = columnText(statement, 2);
        income.amount = sqlite3_column_double(statement, 3);

        std::string description = columnText(statement, 4);
        if (!description.empty())
        {
            income.description = description;
        }

        incomes.push_back(income);
    }

    sqlite3_finalize(statement);
    return incomes;
}

// ==================== SQLiteBudgetRepository ====================

SQLiteBudgetRepository::SQLiteBudgetRepository(Database& database)
    : database_(database)
{
}

int SQLiteBudgetRepository::addOrReplace(const Budget& budget) const
{
    const char* sql = "INSERT INTO budgets (category, amount, period) VALUES (?, ?, ?) "
                      "ON CONFLICT(category) DO UPDATE SET amount = excluded.amount, period = excluded.period;";
    sqlite3_stmt* statement = nullptr;

    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare budget insert or replace statement.");
    }

    sqlite3_bind_text(statement, 1, budget.category.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(statement, 2, budget.amount);
    sqlite3_bind_text(statement, 3, budget.period.c_str(), -1, SQLITE_TRANSIENT);

    int id = executeInsert(statement, const_cast<Database&>(database_));
    sqlite3_finalize(statement);
    return id;
}

std::vector<Budget> SQLiteBudgetRepository::list() const
{
    const char* sql = "SELECT id, category, amount, period FROM budgets ORDER BY category ASC;";
    sqlite3_stmt* statement = nullptr;

    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare budget list query.");
    }

    std::vector<Budget> budgets;
    while ((result = sqlite3_step(statement)) == SQLITE_ROW)
    {
        Budget budget;
        budget.id = sqlite3_column_int(statement, 0);
        budget.category = columnText(statement, 1);
        budget.amount = sqlite3_column_double(statement, 2);
        budget.period = columnText(statement, 3);
        budgets.push_back(budget);
    }

    sqlite3_finalize(statement);
    return budgets;
}

std::optional<Budget> SQLiteBudgetRepository::findByCategory(const std::string& category) const
{
    const char* sql = "SELECT id, category, amount, period FROM budgets WHERE category = ?;";
    sqlite3_stmt* statement = nullptr;

    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare budget find query.");
    }

    sqlite3_bind_text(statement, 1, category.c_str(), -1, SQLITE_TRANSIENT);

    if ((result = sqlite3_step(statement)) == SQLITE_ROW)
    {
        Budget budget;
        budget.id = sqlite3_column_int(statement, 0);
        budget.category = columnText(statement, 1);
        budget.amount = sqlite3_column_double(statement, 2);
        budget.period = columnText(statement, 3);

        sqlite3_finalize(statement);
        return budget;
    }

    sqlite3_finalize(statement);
    return std::nullopt;
}

// ==================== SQLiteUserRepository ====================

SQLiteUserRepository::SQLiteUserRepository(Database& database)
    : database_(database)
{
}

int SQLiteUserRepository::add(const User& user) const
{
    const char* sql = "INSERT INTO users (username, password_hash) VALUES (?, ?);";
    sqlite3_stmt* statement = nullptr;

    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare user insert statement.");
    }

    sqlite3_bind_text(statement, 1, user.username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, user.passwordHash.c_str(), -1, SQLITE_TRANSIENT);

    int id = executeInsert(statement, const_cast<Database&>(database_));
    sqlite3_finalize(statement);
    return id;
}

std::optional<User> SQLiteUserRepository::findByUsername(const std::string& username) const
{
    const char* sql = "SELECT id, username, password_hash FROM users WHERE username = ?;";
    sqlite3_stmt* statement = nullptr;

    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare user find query.");
    }

    sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    if ((result = sqlite3_step(statement)) == SQLITE_ROW)
    {
        User user;
        user.id = sqlite3_column_int(statement, 0);
        user.username = columnText(statement, 1);
        user.passwordHash = columnText(statement, 2);

        sqlite3_finalize(statement);
        return user;
    }

    sqlite3_finalize(statement);
    return std::nullopt;
}

} // namespace finance
