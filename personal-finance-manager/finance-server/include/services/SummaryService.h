#ifndef FINANCE_SERVER_SERVICES_SUMMARYSERVICE_H
#define FINANCE_SERVER_SERVICES_SUMMARYSERVICE_H

#include <nlohmann/json.hpp>

namespace services {

class SummaryService {
public:
    nlohmann::json getMonthlySummary(int userId, int month, int year);
    nlohmann::json getCategoryBreakdown(int userId, int month, int year);
};

}

#endif