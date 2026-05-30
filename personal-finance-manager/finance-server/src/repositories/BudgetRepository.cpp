#include "repositories/BudgetRepository.h"
#include "database/Database.h"
#include <spdlog/spdlog.h>

namespace repositories {

std::vector<Budget> BudgetRepository::findByUserId(int userId) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT id, user_id, category, monthly_limit, month, year, CAST(created_at AS CHAR) "
        "FROM finance_db.budgets WHERE user_id = ? ORDER BY year DESC, month DESC")
        .bind(userId)
        .execute();

    std::vector<Budget> budgets;
    for (auto row : result) {
        Budget b;
        b.id = row[0].get<int>();
        b.userId = row[1].get<int>();
        b.category = row[2].get<std::string>();
        b.monthlyLimit = row[3].get<double>();
        b.month = row[4].get<int>();
        b.year = row[5].get<int>();
        b.createdAt = row[6].get<std::string>();
        budgets.push_back(b);
    }
    return budgets;
}

std::optional<Budget> BudgetRepository::findById(int id) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT id, user_id, category, monthly_limit, month, year, CAST(created_at AS CHAR) "
        "FROM finance_db.budgets WHERE id = ?")
        .bind(id)
        .execute();

    auto row = result.fetchOne();
    if (!row) return std::nullopt;

    Budget b;
    b.id = row[0].get<int>();
    b.userId = row[1].get<int>();
    b.category = row[2].get<std::string>();
    b.monthlyLimit = row[3].get<double>();
    b.month = row[4].get<int>();
    b.year = row[5].get<int>();
    b.createdAt = row[6].get<std::string>();
    return b;
}

std::optional<Budget> BudgetRepository::findByUserCategoryMonth(
    int userId, const std::string& category, int month, int year) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT id, user_id, category, monthly_limit, month, year, CAST(created_at AS CHAR) "
        "FROM finance_db.budgets WHERE user_id = ? AND category = ? AND month = ? AND year = ?")
        .bind(userId)
        .bind(category)
        .bind(month)
        .bind(year)
        .execute();

    auto row = result.fetchOne();
    if (!row) return std::nullopt;

    Budget b;
    b.id = row[0].get<int>();
    b.userId = row[1].get<int>();
    b.category = row[2].get<std::string>();
    b.monthlyLimit = row[3].get<double>();
    b.month = row[4].get<int>();
    b.year = row[5].get<int>();
    b.createdAt = row[6].get<std::string>();
    return b;
}

bool BudgetRepository::create(const Budget& budget) {
    try {
        auto& session = database::Database::instance().getSession();
        session.sql(
            "INSERT INTO finance_db.budgets (user_id, category, monthly_limit, month, year) "
            "VALUES (?, ?, ?, ?, ?)")
            .bind(budget.userId)
            .bind(budget.category)
            .bind(budget.monthlyLimit)
            .bind(budget.month)
            .bind(budget.year)
            .execute();
        return true;
    } catch (const std::exception& e) {
        spdlog::error("BudgetRepository::create failed: {}", e.what());
        return false;
    }
}

bool BudgetRepository::update(const Budget& budget) {
    try {
        auto& session = database::Database::instance().getSession();
        session.sql(
            "UPDATE finance_db.budgets SET category = ?, monthly_limit = ?, month = ?, year = ? "
            "WHERE id = ? AND user_id = ?")
            .bind(budget.category)
            .bind(budget.monthlyLimit)
            .bind(budget.month)
            .bind(budget.year)
            .bind(budget.id)
            .bind(budget.userId)
            .execute();
        return true;
    } catch (const std::exception& e) {
        spdlog::error("BudgetRepository::update failed: {}", e.what());
        return false;
    }
}

bool BudgetRepository::remove(int id, int userId) {
    try {
        auto& session = database::Database::instance().getSession();
        session.sql("DELETE FROM finance_db.budgets WHERE id = ? AND user_id = ?")
            .bind(id)
            .bind(userId)
            .execute();
        return true;
    } catch (const std::exception& e) {
        spdlog::error("BudgetRepository::remove failed: {}", e.what());
        return false;
    }
}

}
