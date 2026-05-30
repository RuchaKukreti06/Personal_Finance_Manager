#include "controllers/BudgetController.h"
#include "middleware/AuthMiddleware.h"
#include "middleware/InputValidator.h"
#include "services/BudgetService.h"
#include <nlohmann/json.hpp>

namespace controllers {

void BudgetController::registerRoutes(httplib::Server& server) {
    server.Get("/api/budgets", handleGetBudgets);
    server.Post("/api/budgets", handleAddBudget);
    server.Put("/api/budgets/:id", handleUpdateBudget);
    server.Delete("/api/budgets/:id", handleDeleteBudget);
    server.Get("/api/budgets/alerts", handleCheckAlerts);
}

void BudgetController::handleGetBudgets(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    services::BudgetService service;
    auto result = service.getBudgets(payload->userId);
    response.set_content(result.dump(), "application/json");
}

void BudgetController::handleAddBudget(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    nlohmann::json body;
    if (!middleware::InputValidator::parseJsonBody(request, body, response)) return;

    if (!middleware::InputValidator::hasRequiredFields(body, {"category", "monthlyLimit", "month", "year"})) {
        response.status = 400;
        response.set_content(
            nlohmann::json({{"success", false}, {"error", "Missing required fields"}}).dump(),
            "application/json");
        return;
    }

    services::BudgetService service;
    auto result = service.addBudget(
        payload->userId,
        body["category"].get<std::string>(),
        body["monthlyLimit"].get<double>(),
        body["month"].get<int>(),
        body["year"].get<int>());

    response.status = result["success"].get<bool>() ? 201 : 400;
    response.set_content(result.dump(), "application/json");
}

void BudgetController::handleUpdateBudget(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    int budgetId = std::stoi(request.path_params.at("id"));

    nlohmann::json body;
    if (!middleware::InputValidator::parseJsonBody(request, body, response)) return;

    if (!middleware::InputValidator::hasRequiredFields(body, {"monthlyLimit"})) {
        response.status = 400;
        response.set_content(
            nlohmann::json({{"success", false}, {"error", "Missing required fields"}}).dump(),
            "application/json");
        return;
    }

    services::BudgetService service;
    auto result = service.updateBudget(
        payload->userId,
        budgetId,
        body["monthlyLimit"].get<double>());

    response.status = result["success"].get<bool>() ? 200 : 400;
    response.set_content(result.dump(), "application/json");
}

void BudgetController::handleDeleteBudget(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    int budgetId = std::stoi(request.path_params.at("id"));

    services::BudgetService service;
    auto result = service.deleteBudget(payload->userId, budgetId);
    response.status = result["success"].get<bool>() ? 200 : 400;
    response.set_content(result.dump(), "application/json");
}

void BudgetController::handleCheckAlerts(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    std::string monthStr = request.get_param_value("month");
    std::string yearStr = request.get_param_value("year");

    if (monthStr.empty() || yearStr.empty()) {
        response.status = 400;
        response.set_content(
            nlohmann::json({{"success", false}, {"error", "month and year params required"}}).dump(),
            "application/json");
        return;
    }

    services::BudgetService service;
    auto result = service.checkBudgetAlerts(payload->userId, std::stoi(monthStr), std::stoi(yearStr));
    response.set_content(result.dump(), "application/json");
}

}
