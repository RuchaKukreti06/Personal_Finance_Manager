#include "services/IncomeService.h"
#include "repositories/IncomeRepository.h"
#include "utils/JsonSerializer.h"
#include <spdlog/spdlog.h>

namespace services {

nlohmann::json IncomeService::getIncomes(int userId) {
    repositories::IncomeRepository repo;
    auto incomes = repo.findByUserId(userId);
    return {{"success", true}, {"incomes", serializer::toJsonArray(incomes)}};
}

nlohmann::json IncomeService::getIncomesByDateRange(int userId, const std::string& startDate, const std::string& endDate) {
    repositories::IncomeRepository repo;
    auto incomes = repo.findByUserIdAndDateRange(userId, startDate, endDate);
    return {{"success", true}, {"incomes", serializer::toJsonArray(incomes)}};
}

nlohmann::json IncomeService::addIncome(int userId, double amount, const std::string& source,
                                         const std::string& description, const std::string& date) {
    if (amount <= 0) {
        return {{"success", false}, {"error", "Amount must be positive"}};
    }
    if (source.empty() || date.empty()) {
        return {{"success", false}, {"error", "Source and date are required"}};
    }

    Income income;
    income.userId = userId;
    income.amount = amount;
    income.source = source;
    income.description = description;
    income.date = date;

    repositories::IncomeRepository repo;
    if (!repo.create(income)) {
        return {{"success", false}, {"error", "Failed to add income"}};
    }

    spdlog::info("Income added: userId={} amount={} source={}", userId, amount, source);
    return {{"success", true}, {"message", "Income added"}};
}

nlohmann::json IncomeService::updateIncome(int userId, int incomeId, double amount,
                                            const std::string& source, const std::string& description,
                                            const std::string& date) {
    repositories::IncomeRepository repo;
    auto existing = repo.findById(incomeId);

    if (!existing || existing->userId != userId) {
        return {{"success", false}, {"error", "Income not found"}};
    }
    if (amount <= 0) {
        return {{"success", false}, {"error", "Amount must be positive"}};
    }

    Income updated = *existing;
    updated.amount = amount;
    updated.source = source;
    updated.description = description;
    updated.date = date;

    if (!repo.update(updated)) {
        return {{"success", false}, {"error", "Failed to update income"}};
    }

    return {{"success", true}, {"message", "Income updated"}};
}

nlohmann::json IncomeService::deleteIncome(int userId, int incomeId) {
    repositories::IncomeRepository repo;
    auto existing = repo.findById(incomeId);

    if (!existing || existing->userId != userId) {
        return {{"success", false}, {"error", "Income not found"}};
    }

    if (!repo.remove(incomeId, userId)) {
        return {{"success", false}, {"error", "Failed to delete income"}};
    }

    return {{"success", true}, {"message", "Income deleted"}};
}

}