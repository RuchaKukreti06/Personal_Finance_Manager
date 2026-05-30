#ifndef FINANCE_SERVER_SERVICES_INCOMESERVICE_H
#define FINANCE_SERVER_SERVICES_INCOMESERVICE_H

#include <nlohmann/json.hpp>
#include <string>

namespace services {

class IncomeService {
public:
    nlohmann::json getIncomes(int userId);
    nlohmann::json getIncomesByDateRange(int userId, const std::string& startDate, const std::string& endDate);
    nlohmann::json addIncome(int userId, double amount, const std::string& source, const std::string& description, const std::string& date);
    nlohmann::json updateIncome(int userId, int incomeId, double amount, const std::string& source, const std::string& description, const std::string& date);
    nlohmann::json deleteIncome(int userId, int incomeId);
};

}

#endif