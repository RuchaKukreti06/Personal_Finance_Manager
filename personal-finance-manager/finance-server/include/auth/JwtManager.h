#ifndef FINANCE_SERVER_AUTH_JWTMANAGER_H
#define FINANCE_SERVER_AUTH_JWTMANAGER_H

#include <string>
#include <optional>

namespace auth {

struct TokenPayload {
    int userId = 0;
    std::string username;
};

class JwtManager {
public:
    static JwtManager& instance();

    void configure(const std::string& secret, int expirationMinutes);
    std::string generate(int userId, const std::string& username);
    std::optional<TokenPayload> validate(const std::string& token);

private:
    JwtManager() = default;
    std::string secret_;
    int expirationMinutes_ = 60;
};

}

#endif