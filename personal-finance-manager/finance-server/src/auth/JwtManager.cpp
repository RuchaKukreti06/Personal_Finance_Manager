#include "auth/JwtManager.h"
#include <jwt-cpp/jwt.h>
#include <chrono>
#include <spdlog/spdlog.h>

using traits = jwt::traits::nlohmann_json;

namespace auth {

JwtManager& JwtManager::instance() {
    static JwtManager inst;
    return inst;
}

void JwtManager::configure(const std::string& secret, int expirationMinutes) {
    secret_ = secret;
    expirationMinutes_ = expirationMinutes;
}

std::string JwtManager::generate(int userId, const std::string& username) {
    auto token = jwt::create<traits>()
        .set_issuer("finance-server")
        .set_type("JWT")
        .set_payload_claim("user_id", jwt::basic_claim<traits>(std::to_string(userId)))
        .set_payload_claim("username", jwt::basic_claim<traits>(username))
        .set_issued_at(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now() +
            std::chrono::minutes(expirationMinutes_))
        .sign(jwt::algorithm::hs256{secret_});
    return token;
}

std::optional<TokenPayload> JwtManager::validate(const std::string& token) {
    try {
        auto decoded = jwt::decode<traits>(token);
        auto verifier = jwt::verify<traits>()
            .allow_algorithm(jwt::algorithm::hs256{secret_})
            .with_issuer("finance-server");
        verifier.verify(decoded);

        TokenPayload payload;
        payload.userId = std::stoi(decoded.get_payload_claim("user_id").as_string());
        payload.username = decoded.get_payload_claim("username").as_string();
        return payload;
    } catch (const std::exception& e) {
        spdlog::debug("JWT validation failed: {}", e.what());
        return std::nullopt;
    }
}

}