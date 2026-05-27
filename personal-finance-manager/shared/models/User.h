#ifndef SHARED_MODELS_USER_H
#define SHARED_MODELS_USER_H

#include <string>

struct User {
    int id = 0;
    std::string username;
    std::string email;
    std::string passwordHash;
    std::string createdAt;
};

#endif
