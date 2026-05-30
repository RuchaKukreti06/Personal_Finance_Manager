#include "controllers/AuthController.h"
#include "middleware/InputValidator.h"
#include "middleware/AuthMiddleware.h"
#include "services/AuthService.h"
#include <nlohmann/json.hpp>

namespace controllers {

void AuthController::registerRoutes(httplib::Server& server) {
    server.Post("/api/auth/register", handleRegister);
    server.Post("/api/auth/login", handleLogin);
    server.Post("/api/auth/change-password", handleChangePassword);
}

void AuthController::handleRegister(const httplib::Request& request, httplib::Response& response) {
    nlohmann::json body;
    if (!middleware::InputValidator::parseJsonBody(request, body, response)) return;

    if (!middleware::InputValidator::hasRequiredFields(body, {"username", "email", "password"})) {
        response.status = 400;
        response.set_content(
            nlohmann::json({{"success", false}, {"error", "Missing required fields"}}).dump(),
            "application/json");
        return;
    }

    services::AuthService authService;
    auto result = authService.registerUser(
        body["username"].get<std::string>(),
        body["email"].get<std::string>(),
        body["password"].get<std::string>());

    response.status = result["success"].get<bool>() ? 201 : 400;
    response.set_content(result.dump(), "application/json");
}

void AuthController::handleLogin(const httplib::Request& request, httplib::Response& response) {
    nlohmann::json body;
    if (!middleware::InputValidator::parseJsonBody(request, body, response)) return;

    if (!middleware::InputValidator::hasRequiredFields(body, {"username", "password"})) {
        response.status = 400;
        response.set_content(
            nlohmann::json({{"success", false}, {"error", "Missing required fields"}}).dump(),
            "application/json");
        return;
    }

    services::AuthService authService;
    auto result = authService.login(
        body["username"].get<std::string>(),
        body["password"].get<std::string>());

    response.status = result["success"].get<bool>() ? 200 : 401;
    response.set_content(result.dump(), "application/json");
}

void AuthController::handleChangePassword(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    nlohmann::json body;
    if (!middleware::InputValidator::parseJsonBody(request, body, response)) return;

    if (!middleware::InputValidator::hasRequiredFields(body, {"oldPassword", "newPassword"})) {
        response.status = 400;
        response.set_content(
            nlohmann::json({{"success", false}, {"error", "Missing required fields"}}).dump(),
            "application/json");
        return;
    }

    services::AuthService authService;
    auto result = authService.changePassword(
        payload->userId,
        body["oldPassword"].get<std::string>(),
        body["newPassword"].get<std::string>());

    response.status = result["success"].get<bool>() ? 200 : 400;
    response.set_content(result.dump(), "application/json");
}

}
