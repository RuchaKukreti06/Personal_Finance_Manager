#include "controllers/IncomeController.h"
#include "middleware/AuthMiddleware.h"
#include "middleware/InputValidator.h"
#include "services/IncomeService.h"
#include <nlohmann/json.hpp>

namespace controllers {

void IncomeController::registerRoutes(httplib::Server& server) {
    server.Get("/api/incomes", handleGetIncomes);
    server.Get("/api/incomes/range", handleGetByDateRange);
    server.Post("/api/incomes", handleAddIncome);
    server.Put("/api/incomes/:id", handleUpdateIncome);
    server.Delete("/api/incomes/:id", handleDeleteIncome);
}

void IncomeController::handleGetIncomes(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    services::IncomeService service;
    auto result = service.getIncomes(payload->userId);
    response.set_content(result.dump(), "application/json");
}

void IncomeController::handleGetByDateRange(const httplib::Request& request, httplib::Response& response) {
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

    services::IncomeService service;
    auto result = service.getIncomesByDateRange(payload->userId, startDate, endDate);
    response.set_content(result.dump(), "application/json");
}

void IncomeController::handleAddIncome(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    nlohmann::json body;
    if (!middleware::InputValidator::parseJsonBody(request, body, response)) return;

    if (!middleware::InputValidator::hasRequiredFields(body, {"amount", "source", "date"})) {
        response.status = 400;
        response.set_content(
            nlohmann::json({{"success", false}, {"error", "Missing required fields"}}).dump(),
            "application/json");
        return;
    }

    services::IncomeService service;
    auto result = service.addIncome(
        payload->userId,
        body["amount"].get<double>(),
        body["source"].get<std::string>(),
        body.value("description", ""),
        body["date"].get<std::string>());

    response.status = result["success"].get<bool>() ? 201 : 400;
    response.set_content(result.dump(), "application/json");
}

void IncomeController::handleUpdateIncome(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    int incomeId = std::stoi(request.path_params.at("id"));

    nlohmann::json body;
    if (!middleware::InputValidator::parseJsonBody(request, body, response)) return;

    if (!middleware::InputValidator::hasRequiredFields(body, {"amount", "source", "date"})) {
        response.status = 400;
        response.set_content(
            nlohmann::json({{"success", false}, {"error", "Missing required fields"}}).dump(),
            "application/json");
        return;
    }

    services::IncomeService service;
    auto result = service.updateIncome(
        payload->userId,
        incomeId,
        body["amount"].get<double>(),
        body["source"].get<std::string>(),
        body.value("description", ""),
        body["date"].get<std::string>());

    response.status = result["success"].get<bool>() ? 200 : 400;
    response.set_content(result.dump(), "application/json");
}

void IncomeController::handleDeleteIncome(const httplib::Request& request, httplib::Response& response) {
    auto payload = middleware::AuthMiddleware::authenticate(request);
    if (!payload) {
        middleware::AuthMiddleware::handleUnauthorized(response);
        return;
    }

    int incomeId = std::stoi(request.path_params.at("id"));

    services::IncomeService service;
    auto result = service.deleteIncome(payload->userId, incomeId);
    response.status = result["success"].get<bool>() ? 200 : 400;
    response.set_content(result.dump(), "application/json");
}

}
