#ifndef FINANCE_SERVER_SERVICES_BUDGETSERVICE_H
#define FINANCE_SERVER_SERVICES_BUDGETSERVICE_H

#include <nlohmann/json.hpp>
#include <string>

namespace services {

class BudgetService {
public:
    nlohmann::json getBudgets(int userId);
    nlohmann::json addBudget(int userId, const std::string& category, double monthlyLimit, int month, int year);
    nlohmann::json updateBudget(int userId, int budgetId, double monthlyLimit);
    nlohmann::json deleteBudget(int userId, int budgetId);
    nlohmann::json checkBudgetAlerts(int userId, int month, int year);
};

}

#endif