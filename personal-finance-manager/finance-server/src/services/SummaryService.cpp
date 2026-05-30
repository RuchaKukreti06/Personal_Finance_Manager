#include "services/SummaryService.h"
#include "repositories/ExpenseRepository.h"
#include "repositories/IncomeRepository.h"
#include "utils/Constants.h"
#include "utils/DateUtils.h"
#include <map>

namespace services {

nlohmann::json SummaryService::getMonthlySummary(int userId, int month, int year) {
    auto [startDate, endDate] = utils::getMonthDateRange(month, year);

    repositories::ExpenseRepository expenseRepo;
    repositories::IncomeRepository incomeRepo;

    auto expenses = expenseRepo.findByUserIdAndDateRange(userId, startDate, endDate);
    auto incomes = incomeRepo.findByUserIdAndDateRange(userId, startDate, endDate);

    double totalExpenses = 0.0;
    for (const auto& expense : expenses) totalExpenses += expense.amount;

    double totalIncomes = 0.0;
    for (const auto& income : incomes) totalIncomes += income.amount;

    double balance = totalIncomes - totalExpenses;

    return {
        {"success", true},
        {"month", month},
        {"year", year},
        {"totalIncome", totalIncomes},
        {"totalExpense", totalExpenses},
        {"balance", balance},
        {"transactionCount", expenses.size() + incomes.size()}
    };
}

nlohmann::json SummaryService::getCategoryBreakdown(int userId, int month, int year) {
    auto [startDate, endDate] = utils::getMonthDateRange(month, year);

    repositories::ExpenseRepository repo;
    auto expenses = repo.findByUserIdAndDateRange(userId, startDate, endDate);

    std::map<std::string, double> categoryTotals;
    double grandTotal = 0.0;

    for (const auto& expense : expenses) {
        categoryTotals[expense.category] += expense.amount;
        grandTotal += expense.amount;
    }

    nlohmann::json categories = nlohmann::json::array();
    for (const auto& [category, total] : categoryTotals) {
        double percentage = (grandTotal > 0)
            ? (total / grandTotal * constants::validation::PERCENTAGE_MULTIPLIER)
            : 0.0;
        categories.push_back({
            {"category", category},
            {"total", total},
            {"percentage", static_cast<int>(percentage)}
        });
    }

    return {
        {"success", true},
        {"month", month},
        {"year", year},
        {"grandTotal", grandTotal},
        {"categories", categories}
    };
}

}