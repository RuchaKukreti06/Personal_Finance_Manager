#include "Repository.h"

#include <stdexcept>

namespace
{
std::string columnText(sqlite3_stmt* statement, int index)
{
    const unsigned char* text = sqlite3_column_text(statement, index);
    return text ? reinterpret_cast<const char*>(text) : std::string();
}
}

ExpenseRepository::ExpenseRepository(Database& database)
    : database_(database)
{
}

int ExpenseRepository::add(Expense const& expense) const
{
    sqlite3_stmt* statement = nullptr;
    const char* sql = "INSERT INTO expenses (date, category, amount, description) VALUES (?, ?, ?, ?);";
    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare statement for expense insertion.");
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

    result = sqlite3_step(statement);
    if (result != SQLITE_DONE)
    {
        sqlite3_finalize(statement);
        throw std::runtime_error("Failed to insert expense.");
    }

    int id = static_cast<int>(sqlite3_last_insert_rowid(database_.connection()));
    sqlite3_finalize(statement);
    return id;
}

std::vector<Expense> ExpenseRepository::list() const
{
    const char* sql = "SELECT id, date, category, amount, description FROM expenses ORDER BY date DESC;";
    sqlite3_stmt* statement = nullptr;
    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare expense list query.");
    }

    std::vector<Expense> items;
    while ((result = sqlite3_step(statement)) == SQLITE_ROW)
    {
        Expense item;
        item.id = sqlite3_column_int(statement, 0);
        item.date = columnText(statement, 1);
        item.category = columnText(statement, 2);
        item.amount = sqlite3_column_double(statement, 3);
        std::string description = columnText(statement, 4);
        if (!description.empty())
        {
            item.description = description;
        }
        items.push_back(item);
    }
    sqlite3_finalize(statement);
    return items;
}

std::vector<Expense> ExpenseRepository::filter(std::string const& category, std::string const& startDate, std::string const& endDate) const
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
            {
                sql += " AND ";
            }
            sql += "date >= ?";
            firstClause = false;
        }
        if (hasEndDate)
        {
            if (!firstClause)
            {
                sql += " AND ";
            }
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

    std::vector<Expense> items;
    while ((result = sqlite3_step(statement)) == SQLITE_ROW)
    {
        Expense item;
        item.id = sqlite3_column_int(statement, 0);
        item.date = columnText(statement, 1);
        item.category = columnText(statement, 2);
        item.amount = sqlite3_column_double(statement, 3);
        std::string description = columnText(statement, 4);
        if (!description.empty())
        {
            item.description = description;
        }
        items.push_back(item);
    }
    sqlite3_finalize(statement);
    return items;
}

bool ExpenseRepository::remove(int expenseId) const
{
    sqlite3_stmt* statement = nullptr;
    const char* sql = "DELETE FROM expenses WHERE id = ?;";
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

IncomeRepository::IncomeRepository(Database& database)
    : database_(database)
{
}

int IncomeRepository::add(Income const& income) const
{
    sqlite3_stmt* statement = nullptr;
    const char* sql = "INSERT INTO income (date, source, amount, description) VALUES (?, ?, ?, ?);";
    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare statement for income insertion.");
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

    result = sqlite3_step(statement);
    if (result != SQLITE_DONE)
    {
        sqlite3_finalize(statement);
        throw std::runtime_error("Failed to insert income.");
    }

    int id = static_cast<int>(sqlite3_last_insert_rowid(database_.connection()));
    sqlite3_finalize(statement);
    return id;
}

std::vector<Income> IncomeRepository::list() const
{
    const char* sql = "SELECT id, date, source, amount, description FROM income ORDER BY date DESC;";
    sqlite3_stmt* statement = nullptr;
    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare income list query.");
    }

    std::vector<Income> items;
    while ((result = sqlite3_step(statement)) == SQLITE_ROW)
    {
        Income item;
        item.id = sqlite3_column_int(statement, 0);
        item.date = columnText(statement, 1);
        item.source = columnText(statement, 2);
        item.amount = sqlite3_column_double(statement, 3);
        std::string description = columnText(statement, 4);
        if (!description.empty())
        {
            item.description = description;
        }
        items.push_back(item);
    }
    sqlite3_finalize(statement);
    return items;
}

BudgetRepository::BudgetRepository(Database& database)
    : database_(database)
{
}

int BudgetRepository::addOrReplace(Budget const& budget) const
{
    sqlite3_stmt* statement = nullptr;
    const char* sql = "INSERT OR REPLACE INTO budgets (category, amount, period) VALUES (?, ?, ?);";
    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare statement for budget insertion.");
    }

    sqlite3_bind_text(statement, 1, budget.category.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(statement, 2, budget.amount);
    sqlite3_bind_text(statement, 3, budget.period.c_str(), -1, SQLITE_TRANSIENT);
    result = sqlite3_step(statement);
    if (result != SQLITE_DONE)
    {
        sqlite3_finalize(statement);
        throw std::runtime_error("Failed to insert budget.");
    }

    int id = static_cast<int>(sqlite3_last_insert_rowid(database_.connection()));
    sqlite3_finalize(statement);
    return id;
}

std::vector<Budget> BudgetRepository::list() const
{
    const char* sql = "SELECT id, category, amount, period FROM budgets ORDER BY category ASC;";
    sqlite3_stmt* statement = nullptr;
    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare budget list query.");
    }

    std::vector<Budget> items;
    while ((result = sqlite3_step(statement)) == SQLITE_ROW)
    {
        Budget item;
        item.id = sqlite3_column_int(statement, 0);
        item.category = columnText(statement, 1);
        item.amount = sqlite3_column_double(statement, 2);
        item.period = columnText(statement, 3);
        items.push_back(item);
    }
    sqlite3_finalize(statement);
    return items;
}

std::optional<Budget> BudgetRepository::findByCategory(std::string const& category) const
{
    sqlite3_stmt* statement = nullptr;
    const char* sql = "SELECT id, category, amount, period FROM budgets WHERE category = ?;";
    int result = sqlite3_prepare_v2(database_.connection(), sql, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare budget query.");
    }

    sqlite3_bind_text(statement, 1, category.c_str(), -1, SQLITE_TRANSIENT);
    result = sqlite3_step(statement);
    if (result == SQLITE_ROW)
    {
        Budget item;
        item.id = sqlite3_column_int(statement, 0);
        item.category = columnText(statement, 1);
        item.amount = sqlite3_column_double(statement, 2);
        item.period = columnText(statement, 3);
        sqlite3_finalize(statement);
        return item;
    }

    sqlite3_finalize(statement);
    return std::nullopt;
}
