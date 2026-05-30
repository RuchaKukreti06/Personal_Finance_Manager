#ifndef SHARED_UTILS_JSONSERIALIZER_H
#define SHARED_UTILS_JSONSERIALIZER_H

#include "models/User.h"
#include "models/Expense.h"
#include "models/Income.h"
#include "models/Budget.h"
#include <nlohmann/json.hpp>

namespace serializer {

inline nlohmann::json toJson(const User& user) {
    return {{"id", user.id}, {"username", user.username}, {"email", user.email}, {"createdAt", user.createdAt}};
}

inline nlohmann::json toJson(const Expense& expense) {
    return {{"id", expense.id}, {"userId", expense.userId}, {"amount", expense.amount},
            {"category", expense.category}, {"description", expense.description},
            {"date", expense.date}, {"createdAt", expense.createdAt}};
}

inline nlohmann::json toJson(const Income& income) {
    return {{"id", income.id}, {"userId", income.userId}, {"amount", income.amount},
            {"source", income.source}, {"description", income.description},
            {"date", income.date}, {"createdAt", income.createdAt}};
}

inline nlohmann::json toJson(const Budget& budget) {
    return {{"id", budget.id}, {"userId", budget.userId}, {"category", budget.category},
            {"monthlyLimit", budget.monthlyLimit}, {"month", budget.month},
            {"year", budget.year}, {"createdAt", budget.createdAt}};
}

template <typename T>
inline nlohmann::json toJsonArray(const std::vector<T>& items) {
    nlohmann::json arr = nlohmann::json::array();
    for (const auto& item : items) {
        arr.push_back(toJson(item));
    }
    return arr;
}

}

#endif
