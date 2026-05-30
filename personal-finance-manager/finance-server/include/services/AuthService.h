#ifndef FINANCE_SERVER_SERVICES_AUTHSERVICE_H
#define FINANCE_SERVER_SERVICES_AUTHSERVICE_H

#include <nlohmann/json.hpp>
#include <string>

namespace services {

class AuthService {
public:
    nlohmann::json registerUser(const std::string& username, const std::string& email, const std::string& password);
    nlohmann::json login(const std::string& username, const std::string& password);
    nlohmann::json changePassword(int userId, const std::string& oldPassword, const std::string& newPassword);
};

}

#endif