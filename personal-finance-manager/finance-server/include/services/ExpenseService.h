#ifndef FINANCE_SERVER_SERVICES_EXPENSESERVICE_H
#define FINANCE_SERVER_SERVICES_EXPENSESERVICE_H

#include <nlohmann/json.hpp>
#include <string>

namespace services {

class ExpenseService {
public:
    nlohmann::json getExpenses(int userId);
    nlohmann::json getExpensesByDateRange(int userId, const std::string& startDate, const std::string& endDate);
    nlohmann::json getExpensesByCategory(int userId, const std::string& category);
    nlohmann::json addExpense(int userId, double amount, const std::string& category, const std::string& description, const std::string& date);
    nlohmann::json updateExpense(int userId, int expenseId, double amount, const std::string& category, const std::string& description, const std::string& date);
    nlohmann::json deleteExpense(int userId, int expenseId);
};

}

#endif