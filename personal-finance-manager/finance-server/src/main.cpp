#include "utils/ConfigLoader.h"
#include "utils/Logger.h"
#include "database/Database.h"
#include "auth/JwtManager.h"
#include "middleware/RateLimiter.h"
#include "controllers/AuthController.h"
#include "controllers/ExpenseController.h"
#include "controllers/IncomeController.h"
#include "controllers/BudgetController.h"
#include "controllers/SummaryController.h"

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <fmt/core.h>
#include <filesystem>

int main(int argc, char* argv[]) {
    try {
        std::string configPath = "config/config.json";
        if (argc > 1) {
            configPath = argv[1];
        }

        auto& config = utils::ConfigLoader::instance();
        config.load(configPath);

        std::filesystem::create_directories("logs");
        utils::Logger::init(config.logLevel(), config.logFile());

        auth::JwtManager::instance().configure(config.jwtSecret(), config.jwtExpirationMinutes());

        auto& db = database::Database::instance();
        db.connect(config.dbHost(), config.dbPort(), config.dbUser(), config.dbPassword(), config.dbName());

        httplib::Server server;

        server.set_pre_routing_handler([](const httplib::Request& request, httplib::Response& response) -> httplib::Server::HandlerResponse {
            if (!middleware::RateLimiter::instance().isAllowed(request.remote_addr)) {
                response.status = 429;
                response.set_content(
                    nlohmann::json({{"success", false}, {"error", "Too many requests"}}).dump(),
                    "application/json");
                return httplib::Server::HandlerResponse::Handled;
            }
            return httplib::Server::HandlerResponse::Unhandled;
        });

        server.Get("/health", [&](const httplib::Request&, httplib::Response& response) {
            nlohmann::json body;
            body["status"] = "ok";
            body["database"] = db.isConnected() ? "connected" : "disconnected";
            response.set_content(body.dump(), "application/json");
        });

        controllers::AuthController::registerRoutes(server);
        controllers::ExpenseController::registerRoutes(server);
        controllers::IncomeController::registerRoutes(server);
        controllers::BudgetController::registerRoutes(server);
        controllers::SummaryController::registerRoutes(server);

        spdlog::info("Starting server on {}:{}", config.serverHost(), config.serverPort());
        server.listen(config.serverHost(), config.serverPort());
    } catch (const std::exception& exception) {
        fmt::print(stderr, "Fatal: {}\n", exception.what());
        return 1;
    }

    return 0;
}
