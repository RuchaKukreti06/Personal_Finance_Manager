#ifndef SHARED_MODELS_INCOME_H
#define SHARED_MODELS_INCOME_H

#include <string>

struct Income {
    int id = 0;
    int userId = 0;
    double amount = 0.0;
    std::string source;
    std::string description;
    std::string date;
    std::string createdAt;
};

#endif
