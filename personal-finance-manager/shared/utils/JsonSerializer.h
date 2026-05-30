#ifndef SHARED_UTILS_JSONSERIALIZER_H
#define SHARED_UTILS_JSONSERIALIZER_H

#include "models/User.h"
#include "models/Expense.h"
#include "models/Income.h"
#include "models/Budget.h"
#include <nlohmann/json.hpp>

namespace serializer {

inline nlohmann::json toJson(const User& u) {
    return {{"id", u.id}, {"username", u.username}, {"email", u.email}, {"createdAt", u.createdAt}};
}

inline nlohmann::json toJson(const Expense& e) {
    return {{"id", e.id}, {"userId", e.userId}, {"amount", e.amount},
            {"category", e.category}, {"description", e.description},
            {"date", e.date}, {"createdAt", e.createdAt}};
}

inline nlohmann::json toJson(const Income& i) {
    return {{"id", i.id}, {"userId", i.userId}, {"amount", i.amount},
            {"source", i.source}, {"description", i.description},
            {"date", i.date}, {"createdAt", i.createdAt}};
}

inline nlohmann::json toJson(const Budget& b) {
    return {{"id", b.id}, {"userId", b.userId}, {"category", b.category},
            {"monthlyLimit", b.monthlyLimit}, {"month", b.month},
            {"year", b.year}, {"createdAt", b.createdAt}};
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