#include "repositories/IncomeRepository.h"
#include "database/Database.h"
#include <spdlog/spdlog.h>

namespace repositories {

std::vector<Income> IncomeRepository::findByUserId(int userId) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT id, user_id, amount, source, description, CAST(date AS CHAR), CAST(created_at AS CHAR) "
        "FROM finance_db.incomes WHERE user_id = ? ORDER BY date DESC")
        .bind(userId)
        .execute();

    std::vector<Income> incomes;
    for (auto row : result) {
        Income i;
        i.id = row[0].get<int>();
        i.userId = row[1].get<int>();
        i.amount = row[2].get<double>();
        i.source = row[3].get<std::string>();
        i.description = row[4].isNull() ? "" : row[4].get<std::string>();
        i.date = row[5].get<std::string>();
        i.createdAt = row[6].get<std::string>();
        incomes.push_back(i);
    }
    return incomes;
}

std::vector<Income> IncomeRepository::findByUserIdAndDateRange(
    int userId, const std::string& startDate, const std::string& endDate) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT id, user_id, amount, source, description, CAST(date AS CHAR), CAST(created_at AS CHAR) "
        "FROM finance_db.incomes WHERE user_id = ? AND date BETWEEN ? AND ? ORDER BY date DESC")
        .bind(userId)
        .bind(startDate)
        .bind(endDate)
        .execute();

    std::vector<Income> incomes;
    for (auto row : result) {
        Income i;
        i.id = row[0].get<int>();
        i.userId = row[1].get<int>();
        i.amount = row[2].get<double>();
        i.source = row[3].get<std::string>();
        i.description = row[4].isNull() ? "" : row[4].get<std::string>();
        i.date = row[5].get<std::string>();
        i.createdAt = row[6].get<std::string>();
        incomes.push_back(i);
    }
    return incomes;
}

std::optional<Income> IncomeRepository::findById(int id) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT id, user_id, amount, source, description, CAST(date AS CHAR), CAST(created_at AS CHAR) "
        "FROM finance_db.incomes WHERE id = ?")
        .bind(id)
        .execute();

    auto row = result.fetchOne();
    if (!row) return std::nullopt;

    Income i;
    i.id = row[0].get<int>();
    i.userId = row[1].get<int>();
    i.amount = row[2].get<double>();
    i.source = row[3].get<std::string>();
    i.description = row[4].isNull() ? "" : row[4].get<std::string>();
    i.date = row[5].get<std::string>();
    i.createdAt = row[6].get<std::string>();
    return i;
}

bool IncomeRepository::create(const Income& income) {
    try {
        auto& session = database::Database::instance().getSession();
        session.sql(
            "INSERT INTO finance_db.incomes (user_id, amount, source, description, date) "
            "VALUES (?, ?, ?, ?, ?)")
            .bind(income.userId)
            .bind(income.amount)
            .bind(income.source)
            .bind(income.description)
            .bind(income.date)
            .execute();
        return true;
    } catch (const std::exception& e) {
        spdlog::error("IncomeRepository::create failed: {}", e.what());
        return false;
    }
}

bool IncomeRepository::update(const Income& income) {
    try {
        auto& session = database::Database::instance().getSession();
        session.sql(
            "UPDATE finance_db.incomes SET amount = ?, source = ?, description = ?, date = ? "
            "WHERE id = ? AND user_id = ?")
            .bind(income.amount)
            .bind(income.source)
            .bind(income.description)
            .bind(income.date)
            .bind(income.id)
            .bind(income.userId)
            .execute();
        return true;
    } catch (const std::exception& e) {
        spdlog::error("IncomeRepository::update failed: {}", e.what());
        return false;
    }
}

bool IncomeRepository::remove(int id, int userId) {
    try {
        auto& session = database::Database::instance().getSession();
        session.sql("DELETE FROM finance_db.incomes WHERE id = ? AND user_id = ?")
            .bind(id)
            .bind(userId)
            .execute();
        return true;
    } catch (const std::exception& e) {
        spdlog::error("IncomeRepository::remove failed: {}", e.what());
        return false;
    }
}

}
