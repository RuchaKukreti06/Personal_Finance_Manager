#ifndef FINANCE_CLIENT_API_AUTHSESSION_H
#define FINANCE_CLIENT_API_AUTHSESSION_H

#include <string>

namespace api {

class AuthSession {
public:
    static AuthSession& instance();

    void login(const std::string& token, const std::string& username);
    void logout();
    bool isLoggedIn() const;
    const std::string& token() const;
    const std::string& username() const;

private:
    AuthSession() = default;
    std::string token_;
    std::string username_;
    bool loggedIn_ = false;
};

}

#endif