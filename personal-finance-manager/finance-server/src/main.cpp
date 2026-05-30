#include "utils/ConfigLoader.h"
#include "utils/Logger.h"
#include "database/Database.h"
#include "auth/JwtManager.h"

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

        server.Get("/health", [&](const httplib::Request&, httplib::Response& res) {
            nlohmann::json body;
            body["status"] = "ok";
            body["database"] = db.isConnected() ? "connected" : "disconnected";
            res.set_content(body.dump(), "application/json");
        });

        spdlog::info("Starting server on {}:{}", config.serverHost(), config.serverPort());
        server.listen(config.serverHost(), config.serverPort());
    } catch (const std::exception& e) {
        fmt::print(stderr, "Fatal: {}\n", e.what());
        return 1;
    }

    return 0;
}
