#include "api/AuthSession.h"

namespace api {

AuthSession& AuthSession::instance() {
    static AuthSession inst;
    return inst;
}

void AuthSession::login(const std::string& token, const std::string& username) {
    token_ = token;
    username_ = username;
    loggedIn_ = true;
}

void AuthSession::logout() {
    token_.clear();
    username_.clear();
    loggedIn_ = false;
}

bool AuthSession::isLoggedIn() const {
    return loggedIn_;
}

const std::string& AuthSession::token() const {
    return token_;
}

const std::string& AuthSession::username() const {
    return username_;
}

}