#include "middleware/AuthMiddleware.h"
#include <nlohmann/json.hpp>

namespace middleware {

static const std::string BEARER_PREFIX = "Bearer ";

std::optional<auth::TokenPayload> AuthMiddleware::authenticate(const httplib::Request& request) {
    auto authHeader = request.get_header_value("Authorization");
    if (authHeader.empty() || authHeader.substr(0, BEARER_PREFIX.size()) != BEARER_PREFIX) {
        return std::nullopt;
    }

    std::string token = authHeader.substr(BEARER_PREFIX.size());
    return auth::JwtManager::instance().validate(token);
}

void AuthMiddleware::handleUnauthorized(httplib::Response& response) {
    nlohmann::json body = {{"success", false}, {"error", "Unauthorized"}};
    response.status = 401;
    response.set_content(body.dump(), "application/json");
}

}
