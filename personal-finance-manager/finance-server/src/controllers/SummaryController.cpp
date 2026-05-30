#include "controllers/SummaryController.h"
#include "middleware/AuthMiddleware.h"
#include "services/SummaryService.h"
#include <nlohmann/json.hpp>

namespace controllers {

void SummaryController::registerRoutes(httplib::Server& server) {
    server.Get("/api/summary/monthly", handleMonthlySummary);
    server.Get("/api/summary/categories", handleCategoryBreakdown);
}

void SummaryController::handleMonthlySummary(const httplib::Request& request, httplib::Response& response) {
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

    services::SummaryService service;
    auto result = service.getMonthlySummary(payload->userId, std::stoi(monthStr), std::stoi(yearStr));
    response.set_content(result.dump(), "application/json");
}

void SummaryController::handleCategoryBreakdown(const httplib::Request& request, httplib::Response& response) {
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

    services::SummaryService service;
    auto result = service.getCategoryBreakdown(payload->userId, std::stoi(monthStr), std::stoi(yearStr));
    response.set_content(result.dump(), "application/json");
}

}
