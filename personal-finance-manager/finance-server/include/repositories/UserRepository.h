#ifndef FINANCE_SERVER_REPOSITORIES_USERREPOSITORY_H
#define FINANCE_SERVER_REPOSITORIES_USERREPOSITORY_H

#include "models/User.h"
#include <string>
#include <optional>

namespace repositories {

class UserRepository {
public:
    std::optional<User> findByUsername(const std::string& username);
    std::optional<User> findByEmail(const std::string& email);
    std::optional<User> findById(int id);
    bool create(const User& user);
    bool existsByUsername(const std::string& username);
    bool existsByEmail(const std::string& email);
    bool updatePassword(int userId, const std::string& passwordHash);
};

}

#endif
