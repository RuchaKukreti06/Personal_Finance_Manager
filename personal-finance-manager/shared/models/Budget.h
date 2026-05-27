#ifndef SHARED_MODELS_BUDGET_H
#define SHARED_MODELS_BUDGET_H

#include <string>

struct Budget {
    int id = 0;
    int userId = 0;
    std::string category;
    double monthlyLimit = 0.0;
    int month = 0;
    int year = 0;
    std::string createdAt;
};

#endif
