#include "services/ExpenseService.h"
#include "repositories/ExpenseRepository.h"
#include "utils/JsonSerializer.h"
#include <spdlog/spdlog.h>

namespace services {

nlohmann::json ExpenseService::getExpenses(int userId) {
    repositories::ExpenseRepository repo;
    auto expenses = repo.findByUserId(userId);
    return {{"success", true}, {"expenses", serializer::toJsonArray(expenses)}};
}

nlohmann::json ExpenseService::getExpensesByDateRange(int userId, const std::string& startDate, const std::string& endDate) {
    repositories::ExpenseRepository repo;
    auto expenses = repo.findByUserIdAndDateRange(userId, startDate, endDate);
    return {{"success", true}, {"expenses", serializer::toJsonArray(expenses)}};
}

nlohmann::json ExpenseService::getExpensesByCategory(int userId, const std::string& category) {
    repositories::ExpenseRepository repo;
    auto expenses = repo.findByUserIdAndCategory(userId, category);
    return {{"success", true}, {"expenses", serializer::toJsonArray(expenses)}};
}

nlohmann::json ExpenseService::addExpense(int userId, double amount, const std::string& category,
                                           const std::string& description, const std::string& date) {
    if (amount <= 0) {
        return {{"success", false}, {"error", "Amount must be positive"}};
    }
    if (category.empty() || date.empty()) {
        return {{"success", false}, {"error", "Category and date are required"}};
    }

    Expense expense;
    expense.userId = userId;
    expense.amount = amount;
    expense.category = category;
    expense.description = description;
    expense.date = date;

    repositories::ExpenseRepository repo;
    if (!repo.create(expense)) {
        return {{"success", false}, {"error", "Failed to add expense"}};
    }

    spdlog::info("Expense added: userId={} amount={} category={}", userId, amount, category);
    return {{"success", true}, {"message", "Expense added"}};
}

nlohmann::json ExpenseService::updateExpense(int userId, int expenseId, double amount,
                                              const std::string& category, const std::string& description,
                                              const std::string& date) {
    repositories::ExpenseRepository repo;
    auto existing = repo.findById(expenseId);

    if (!existing || existing->userId != userId) {
        return {{"success", false}, {"error", "Expense not found"}};
    }
    if (amount <= 0) {
        return {{"success", false}, {"error", "Amount must be positive"}};
    }

    Expense updated = *existing;
    updated.amount = amount;
    updated.category = category;
    updated.description = description;
    updated.date = date;

    if (!repo.update(updated)) {
        return {{"success", false}, {"error", "Failed to update expense"}};
    }

    return {{"success", true}, {"message", "Expense updated"}};
}

nlohmann::json ExpenseService::deleteExpense(int userId, int expenseId) {
    repositories::ExpenseRepository repo;
    auto existing = repo.findById(expenseId);

    if (!existing || existing->userId != userId) {
        return {{"success", false}, {"error", "Expense not found"}};
    }

    if (!repo.remove(expenseId, userId)) {
        return {{"success", false}, {"error", "Failed to delete expense"}};
    }

    return {{"success", true}, {"message", "Expense deleted"}};
}

}
