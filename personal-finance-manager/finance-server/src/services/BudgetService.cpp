#include "services/BudgetService.h"
#include "repositories/BudgetRepository.h"
#include "repositories/ExpenseRepository.h"
#include "utils/JsonSerializer.h"
#include "utils/Constants.h"
#include "utils/DateUtils.h"
#include <spdlog/spdlog.h>

namespace services {

nlohmann::json BudgetService::getBudgets(int userId) {
    repositories::BudgetRepository repo;
    auto budgets = repo.findByUserId(userId);
    return {{"success", true}, {"budgets", serializer::toJsonArray(budgets)}};
}

nlohmann::json BudgetService::addBudget(int userId, const std::string& category,
                                         double monthlyLimit, int month, int year) {
    if (monthlyLimit <= 0) {
        return {{"success", false}, {"error", "Limit must be positive"}};
    }
    if (category.empty()) {
        return {{"success", false}, {"error", "Category is required"}};
    }
    if (month < constants::validation::MIN_MONTH ||
        month > constants::validation::MAX_MONTH ||
        year < constants::validation::MIN_YEAR) {
        return {{"success", false}, {"error", "Invalid month or year"}};
    }

    repositories::BudgetRepository repo;
    if (repo.findByUserCategoryMonth(userId, category, month, year)) {
        return {{"success", false}, {"error", "Budget already exists for this category/month"}};
    }

    Budget budget;
    budget.userId = userId;
    budget.category = category;
    budget.monthlyLimit = monthlyLimit;
    budget.month = month;
    budget.year = year;

    if (!repo.create(budget)) {
        return {{"success", false}, {"error", "Failed to create budget"}};
    }

    spdlog::info("Budget created: userId={} category={} limit={}", userId, category, monthlyLimit);
    return {{"success", true}, {"message", "Budget created"}};
}

nlohmann::json BudgetService::updateBudget(int userId, int budgetId, double monthlyLimit) {
    repositories::BudgetRepository repo;
    auto existing = repo.findById(budgetId);

    if (!existing || existing->userId != userId) {
        return {{"success", false}, {"error", "Budget not found"}};
    }
    if (monthlyLimit <= 0) {
        return {{"success", false}, {"error", "Limit must be positive"}};
    }

    Budget updated = *existing;
    updated.monthlyLimit = monthlyLimit;

    if (!repo.update(updated)) {
        return {{"success", false}, {"error", "Failed to update budget"}};
    }

    return {{"success", true}, {"message", "Budget updated"}};
}

nlohmann::json BudgetService::deleteBudget(int userId, int budgetId) {
    repositories::BudgetRepository repo;
    auto existing = repo.findById(budgetId);

    if (!existing || existing->userId != userId) {
        return {{"success", false}, {"error", "Budget not found"}};
    }

    if (!repo.remove(budgetId, userId)) {
        return {{"success", false}, {"error", "Failed to delete budget"}};
    }

    return {{"success", true}, {"message", "Budget deleted"}};
}

nlohmann::json BudgetService::checkBudgetAlerts(int userId, int month, int year) {
    repositories::BudgetRepository budgetRepo;
    repositories::ExpenseRepository expenseRepo;

    auto budgets = budgetRepo.findByUserId(userId);
    auto [startDate, endDate] = utils::getMonthDateRange(month, year);
    auto expenses = expenseRepo.findByUserIdAndDateRange(userId, startDate, endDate);

    nlohmann::json alerts = nlohmann::json::array();

    for (const auto& budget : budgets) {
        if (budget.month != month || budget.year != year) continue;

        double spent = 0.0;
        for (const auto& expense : expenses) {
            if (expense.category == budget.category) {
                spent += expense.amount;
            }
        }

        double percentage = (budget.monthlyLimit > 0)
            ? (spent / budget.monthlyLimit * constants::validation::PERCENTAGE_MULTIPLIER)
            : 0.0;

        const char* level = constants::budget::LEVEL_OK;
        if (percentage >= constants::budget::EXCEEDED_THRESHOLD) {
            level = constants::budget::LEVEL_EXCEEDED;
        } else if (percentage >= constants::budget::WARNING_THRESHOLD) {
            level = constants::budget::LEVEL_WARNING;
        }

        alerts.push_back({
            {"category", budget.category},
            {"limit", budget.monthlyLimit},
            {"spent", spent},
            {"percentage", static_cast<int>(percentage)},
            {"level", level}
        });
    }

    return {{"success", true}, {"alerts", alerts}};
}

}
