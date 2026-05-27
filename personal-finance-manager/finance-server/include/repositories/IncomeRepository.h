#ifndef FINANCE_SERVER_REPOSITORIES_INCOMEREPOSITORY_H
#define FINANCE_SERVER_REPOSITORIES_INCOMEREPOSITORY_H

#include "models/Income.h"
#include <vector>
#include <optional>
#include <string>

namespace repositories {

class IncomeRepository {
public:
    std::vector<Income> findByUserId(int userId);
    std::vector<Income> findByUserIdAndDateRange(int userId, const std::string& startDate, const std::string& endDate);
    std::optional<Income> findById(int id);
    bool create(const Income& income);
    bool update(const Income& income);
    bool remove(int id, int userId);
};

}

#endif
