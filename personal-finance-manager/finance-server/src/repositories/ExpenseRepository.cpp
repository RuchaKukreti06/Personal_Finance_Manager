#include "repositories/ExpenseRepository.h"
#include "database/Database.h"
#include <spdlog/spdlog.h>

namespace repositories {

std::vector<Expense> ExpenseRepository::findByUserId(int userId) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT id, user_id, amount, category, description, date, created_at "
        "FROM finance_db.expenses WHERE user_id = ? ORDER BY date DESC")
        .bind(userId)
        .execute();

    std::vector<Expense> expenses;
    for (auto row : result) {
        Expense e;
        e.id = row[0].get<int>();
        e.userId = row[1].get<int>();
        e.amount = row[2].get<double>();
        e.category = row[3].get<std::string>();
        e.description = row[4].isNull() ? "" : row[4].get<std::string>();
        e.date = row[5].get<std::string>();
        e.createdAt = row[6].get<std::string>();
        expenses.push_back(e);
    }
    return expenses;
}

std::vector<Expense> ExpenseRepository::findByUserIdAndDateRange(
    int userId, const std::string& startDate, const std::string& endDate) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT id, user_id, amount, category, description, date, created_at "
        "FROM finance_db.expenses WHERE user_id = ? AND date BETWEEN ? AND ? ORDER BY date DESC")
        .bind(userId)
        .bind(startDate)
        .bind(endDate)
        .execute();

    std::vector<Expense> expenses;
    for (auto row : result) {
        Expense e;
        e.id = row[0].get<int>();
        e.userId = row[1].get<int>();
        e.amount = row[2].get<double>();
        e.category = row[3].get<std::string>();
        e.description = row[4].isNull() ? "" : row[4].get<std::string>();
        e.date = row[5].get<std::string>();
        e.createdAt = row[6].get<std::string>();
        expenses.push_back(e);
    }
    return expenses;
}

std::vector<Expense> ExpenseRepository::findByUserIdAndCategory(
    int userId, const std::string& category) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT id, user_id, amount, category, description, date, created_at "
        "FROM finance_db.expenses WHERE user_id = ? AND category = ? ORDER BY date DESC")
        .bind(userId)
        .bind(category)
        .execute();

    std::vector<Expense> expenses;
    for (auto row : result) {
        Expense e;
        e.id = row[0].get<int>();
        e.userId = row[1].get<int>();
        e.amount = row[2].get<double>();
        e.category = row[3].get<std::string>();
        e.description = row[4].isNull() ? "" : row[4].get<std::string>();
        e.date = row[5].get<std::string>();
        e.createdAt = row[6].get<std::string>();
        expenses.push_back(e);
    }
    return expenses;
}

std::optional<Expense> ExpenseRepository::findById(int id) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT id, user_id, amount, category, description, date, created_at "
        "FROM finance_db.expenses WHERE id = ?")
        .bind(id)
        .execute();

    auto row = result.fetchOne();
    if (!row) return std::nullopt;

    Expense e;
    e.id = row[0].get<int>();
    e.userId = row[1].get<int>();
    e.amount = row[2].get<double>();
    e.category = row[3].get<std::string>();
    e.description = row[4].isNull() ? "" : row[4].get<std::string>();
    e.date = row[5].get<std::string>();
    e.createdAt = row[6].get<std::string>();
    return e;
}

bool ExpenseRepository::create(const Expense& expense) {
    try {
        auto& session = database::Database::instance().getSession();
        session.sql(
            "INSERT INTO finance_db.expenses (user_id, amount, category, description, date) "
            "VALUES (?, ?, ?, ?, ?)")
            .bind(expense.userId)
            .bind(expense.amount)
            .bind(expense.category)
            .bind(expense.description)
            .bind(expense.date)
            .execute();
        return true;
    } catch (const std::exception& e) {
        spdlog::error("ExpenseRepository::create failed: {}", e.what());
        return false;
    }
}

bool ExpenseRepository::update(const Expense& expense) {
    try {
        auto& session = database::Database::instance().getSession();
        session.sql(
            "UPDATE finance_db.expenses SET amount = ?, category = ?, description = ?, date = ? "
            "WHERE id = ? AND user_id = ?")
            .bind(expense.amount)
            .bind(expense.category)
            .bind(expense.description)
            .bind(expense.date)
            .bind(expense.id)
            .bind(expense.userId)
            .execute();
        return true;
    } catch (const std::exception& e) {
        spdlog::error("ExpenseRepository::update failed: {}", e.what());
        return false;
    }
}

bool ExpenseRepository::remove(int id, int userId) {
    try {
        auto& session = database::Database::instance().getSession();
        session.sql("DELETE FROM finance_db.expenses WHERE id = ? AND user_id = ?")
            .bind(id)
            .bind(userId)
            .execute();
        return true;
    } catch (const std::exception& e) {
        spdlog::error("ExpenseRepository::remove failed: {}", e.what());
        return false;
    }
}

}
