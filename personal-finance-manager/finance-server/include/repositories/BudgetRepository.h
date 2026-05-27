#ifndef FINANCE_SERVER_REPOSITORIES_BUDGETREPOSITORY_H
#define FINANCE_SERVER_REPOSITORIES_BUDGETREPOSITORY_H

#include "models/Budget.h"
#include <vector>
#include <optional>
#include <string>

namespace repositories {

class BudgetRepository {
public:
    std::vector<Budget> findByUserId(int userId);
    std::optional<Budget> findById(int id);
    std::optional<Budget> findByUserCategoryMonth(int userId, const std::string& category, int month, int year);
    bool create(const Budget& budget);
    bool update(const Budget& budget);
    bool remove(int id, int userId);
};

}

#endif
