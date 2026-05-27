#ifndef SHARED_MODELS_EXPENSE_H
#define SHARED_MODELS_EXPENSE_H

#include <string>

struct Expense {
    int id = 0;
    int userId = 0;
    double amount = 0.0;
    std::string category;
    std::string description;
    std::string date;
    std::string createdAt;
};

#endif
