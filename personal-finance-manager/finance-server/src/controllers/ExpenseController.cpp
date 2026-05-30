#include "controllers/ExpenseController.h"
#include "middleware/AuthMiddleware.h"
#include "middleware/InputValidator.h"
#include "services/ExpenseService.h"
#include <nlohmann/json.hpp>

namespace controllers {

void ExpenseController::registerRoutes(httplib::Server& server) {
    server.Get("/api/expenses", handleGetExpenses);
    server.Get("/api/expenses/range", handleGetByDateRange);
    server.Get("/api/expenses/category", handleGetByCategory);
    server.Post("/api/expenses", handleAddExpense);
    server.Put("/api/expenses/:id", handleUpdateExpense);
    server.Delete("/api/expenses/:id", handleDeleteExpense);
}

void ExpenseController::handleGetExpenses(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    services::ExpenseService service;
    auto result = service.getExpenses(payload->userId);
    response.set_content(result.dump(), "application/json");
}

void ExpenseController::handleGetByDateRange(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    std::string startDate = request.get_param_value("start");
    std::string endDate = request.get_param_value("end");

    if (startDate.empty() || endDate.empty()) {
        response.status = 400;
        response.set_content(
            nlohmann::json({{"success", false}, {"error", "start and end params required"}}).dump(),
            "application/json");
        return;
    }

    services::ExpenseService service;
    auto result = service.getExpensesByDateRange(payload->userId, startDate, endDate);
    response.set_content(result.dump(), "application/json");
}

void ExpenseController::handleGetByCategory(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    std::string category = request.get_param_value("name");
    if (category.empty()) {
        response.status = 400;
        response.set_content(
            nlohmann::json({{"success", false}, {"error", "name param required"}}).dump(),
            "application/json");
        return;
    }

    services::ExpenseService service;
    auto result = service.getExpensesByCategory(payload->userId, category);
    response.set_content(result.dump(), "application/json");
}

void ExpenseController::handleAddExpense(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    nlohmann::json body;
    if (!middleware::InputValidator::parseJsonBody(request, body, response)) return;

    if (!middleware::InputValidator::hasRequiredFields(body, {"amount", "category", "date"})) {
        response.status = 400;
        response.set_content(
            nlohmann::json({{"success", false}, {"error", "Missing required fields"}}).dump(),
            "application/json");
        return;
    }

    services::ExpenseService service;
    auto result = service.addExpense(
        payload->userId,
        body["amount"].get<double>(),
        body["category"].get<std::string>(),
        body.value("description", ""),
        body["date"].get<std::string>());

    response.status = result["success"].get<bool>() ? 201 : 400;
    response.set_content(result.dump(), "application/json");
}

void ExpenseController::handleUpdateExpense(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    int expenseId = std::stoi(request.path_params.at("id"));

    nlohmann::json body;
    if (!middleware::InputValidator::parseJsonBody(request, body, response)) return;

    if (!middleware::InputValidator::hasRequiredFields(body, {"amount", "category", "date"})) {
        response.status = 400;
        response.set_content(
            nlohmann::json({{"success", false}, {"error", "Missing required fields"}}).dump(),
            "application/json");
        return;
    }

    services::ExpenseService service;
    auto result = service.updateExpense(
        payload->userId,
        expenseId,
        body["amount"].get<double>(),
        body["category"].get<std::string>(),
        body.value("description", ""),
        body["date"].get<std::string>());

    response.status = result["success"].get<bool>() ? 200 : 400;
    response.set_content(result.dump(), "application/json");
}

void ExpenseController::handleDeleteExpense(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    int expenseId = std::stoi(request.path_params.at("id"));

    services::ExpenseService service;
    auto result = service.deleteExpense(payload->userId, expenseId);
    response.status = result["success"].get<bool>() ? 200 : 400;
    response.set_content(result.dump(), "application/json");
}

}
