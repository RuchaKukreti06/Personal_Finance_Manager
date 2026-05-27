#ifndef FINANCE_SERVER_REPOSITORIES_EXPENSEREPOSITORY_H
#define FINANCE_SERVER_REPOSITORIES_EXPENSEREPOSITORY_H

#include "models/Expense.h"
#include <vector>
#include <optional>
#include <string>

namespace repositories {

class ExpenseRepository {
public:
    std::vector<Expense> findByUserId(int userId);
    std::vector<Expense> findByUserIdAndDateRange(int userId, const std::string& startDate, const std::string& endDate);
    std::vector<Expense> findByUserIdAndCategory(int userId, const std::string& category);
    std::optional<Expense> findById(int id);
    bool create(const Expense& expense);
    bool update(const Expense& expense);
    bool remove(int id, int userId);
};

}

#endif
